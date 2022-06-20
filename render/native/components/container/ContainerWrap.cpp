#include "Components.h"
#include "Container.h"

#include <stdlib.h>

#include <QWidget>
#include <QtCore/QObject>

static JSClassID ContainerClassID;

WRAPPED_JS_METHODS(SMainWindow, "container")

static JSValue NativeCompAppendChild(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsObject(argv[0])) {
        COMP_REF* child = (COMP_REF*)JS_GetOpaque3(argv[0]);
        COMP_REF* parent = (COMP_REF*)JS_GetOpaque(this_val, ContainerClassID);
        ((SMainWindow*)(parent->comp))->setCentralWidget((QWidget*)(child->comp));
        printf("container %s append child %s \n", parent->uid, child->uid);
    }
};

static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    WRAPPED_JS_METHODS_REGISTER
    SJS_CFUNC_DEF("appendChild", 0, NativeCompAppendChild),
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

static JSValue ContainerConstructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
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
        proto = JS_GetClassProto(ctx, ContainerClassID);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, ContainerClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    if (!s)
        goto fail;
    s->uid = uid;
    s->comp = SMainWindow::getInstance();

    (static_cast<SMainWindow*>(s->comp))->setObjectName(QString(uid));
    JS_FreeCString(ctx, uid);

    JS_SetOpaque(obj, s);
    printf("container %s created \n", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static void ContainerFinalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, ContainerClassID);
    printf("container %s release\n", th->uid);
    if (th) {
        free(th);
    }
}

static JSClassDef ContainerClass = {
    "container",
    .finalizer = ContainerFinalizer,
};

void NativeComponentContainerInit (JSContext* ctx, JSValue ns) {
    JS_NewClassID(&ContainerClassID);
    JS_NewClass(JS_GetRuntime(ctx), ContainerClassID, &ContainerClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    JS_SetClassProto(ctx, ContainerClassID, proto);

    JSValue obj = JS_NewCFunction2(ctx, ContainerConstructor, "Container", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
    JS_DefinePropertyValueStr(ctx, ns, "Container", obj, JS_PROP_C_W_E);
}

