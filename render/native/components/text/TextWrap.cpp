#include "components/Components.h"
#include "Text.h"

#include <stdlib.h>

static JSClassID TextClassID;

WRAPPED_JS_METHODS(SLabel, "text")

static JSValue native_comp_setText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsString(argv[0])) {
        const char* style = JS_ToCString(ctx, argv[0]);
        COMP_REF* s = (COMP_REF*)JS_GetOpaque(this_val, TextClassID);
        ((SLabel*)(s->comp))->setText(QString(style));
        JS_FreeValue(ctx, argv[0]);
        printf("text %s setText\n", s->uid);
    }
};

static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    WRAPPED_JS_METHODS_REGISTER
    SJS_CFUNC_DEF("setText", 0, native_comp_setText),
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

static JSValue TextConstructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
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
        proto = JS_GetClassProto(ctx, TextClassID);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, TextClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    s->uid = uid;
    s->comp = new SLabel();
    (static_cast<SLabel*>(s->comp))->setObjectName(QString(uid));
    JS_FreeCString(ctx, uid);

    if (!s)
        goto fail;

    JS_SetOpaque(obj, s);
    printf("text %s created \n", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static void FlexLayoutFinalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, TextClassID);
    printf("text %s release \n", th->uid);
    if (th) {
        free(th);
    }
}

static JSClassDef ViewClass = {
    "text",
    .finalizer = FlexLayoutFinalizer,
};

void NativeComponentTextInit (JSContext* ctx, JSValue ns) {
    JS_NewClassID(&TextClassID);
    JS_NewClass(JS_GetRuntime(ctx), TextClassID, &ViewClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    JS_SetClassProto(ctx, TextClassID, proto);

    JSValue obj = JS_NewCFunction2(ctx, TextConstructor, "Text", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
    JS_DefinePropertyValueStr(ctx, ns, "Text", obj, JS_PROP_C_W_E);
}