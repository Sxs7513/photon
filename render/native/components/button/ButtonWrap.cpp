#include "components/Components.h"
#include "Button.h"

#include <stdlib.h>

#include <QWidget>
#include <QString>

static JSClassID ButtonClassID;

WRAPPED_JS_METHODS(SButton, "button")

static JSValue NativeCompSetText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsString(argv[0])) {
        const char* style = JS_ToCString(ctx, argv[0]);
        COMP_REF* s = (COMP_REF*)JS_GetOpaque(this_val, ButtonClassID);
        ((SButton*)(s->comp))->setText(QString(style));
        JS_FreeCString(ctx, style);
        printf("button %s setText\n", s->uid);
    }
};

static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    WRAPPED_JS_METHODS_REGISTER
    SJS_CFUNC_DEF("setText", 0, NativeCompSetText),
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

static JSValue ButtonConstructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
    JSValue proto;
    JSValue obj;
    JSValue arg;
    JSValue jsUid;
    const char* uid;

    COMP_REF *s;

    if (JS_IsObject(argv[0])) {
        arg = argv[0];
        jsUid = JS_GetPropertyStr(ctx, arg, "uid");
        if (JS_IsString(jsUid)) {
            uid = JS_ToCString(ctx, jsUid);
            JS_FreeValue(ctx, jsUid);
        }
    }

    if (JS_IsUndefined(new_target)) {
        proto = JS_GetClassProto(ctx, ButtonClassID);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, ButtonClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    s->uid = uid;
    s->comp = new SButton();

    (static_cast<SButton*>(s->comp))->setObjectName(QString(uid));
    JS_FreeCString(ctx, uid);

    if (!s)
        goto fail;

    JS_SetOpaque(obj, s);
    printf("button %s created \n", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static void ButtonFinalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, ButtonClassID);
    printf("button %s release\n", th->uid);
    if (th) {
        free(th);
    }
}

static JSClassDef ButtonClass = {
    "button",
    .finalizer = ButtonFinalizer,
};

void NativeComponentButtonInit (JSContext* ctx, JSValue ns) {
    JS_NewClassID(&ButtonClassID);
    JS_NewClass(JS_GetRuntime(ctx), ButtonClassID, &ButtonClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    JS_SetClassProto(ctx, ButtonClassID, proto);

    JSValue obj = JS_NewCFunction2(ctx, ButtonConstructor, "Button", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
    JS_DefinePropertyValueStr(ctx, ns, "Button", obj, JS_PROP_C_W_E);
}

