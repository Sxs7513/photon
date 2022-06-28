#include "Input.hpp"

static JSClassID InputClassID;

WRAPPED_JS_METHODS(SInput, "input")

static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    WRAPPED_JS_METHODS_REGISTER
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

static JSValue InputConstructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
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
        proto = JS_GetClassProto(ctx, InputClassID);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, InputClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    s->uid = uid;
    s->comp = new SInput();
    (static_cast<SInput*>(s->comp))->setObjectName(QString(uid));
    JS_FreeCString(ctx, uid);
    
    if (!s)
        goto fail;

    JS_SetOpaque(obj, s);
    printf("input %s created \n", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static void InputFinalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, InputClassID);
    printf("input %s release \n", th->uid);
    if (th) {
        free(th);
    }
}

static JSClassDef InputClass = {
    "input",
    .finalizer = InputFinalizer,
};

void NativeComponentInputInit (JSContext* ctx, JSValue ns) {
    JS_NewClassID(&InputClassID);
    JS_NewClass(JS_GetRuntime(ctx), InputClassID, &InputClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    JS_SetClassProto(ctx, InputClassID, proto);

    JSValue obj = JS_NewCFunction2(ctx, InputConstructor, "Input", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
    JS_DefinePropertyValueStr(ctx, ns, "Input", obj, JS_PROP_C_W_E);
}