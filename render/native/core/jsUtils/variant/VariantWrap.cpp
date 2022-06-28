#include "VariantWrap.hpp"

static JSClassID VariantWrapClassID;

static const JSCFunctionListEntry ComponentProtoFuncs[] = {

};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

JSValue VariantWrapper(QVariant* ref) {
    SJSRuntime* qrt;
    JSContext* ctx;

    qrt = GetSJSInstance();
    ctx = qrt->ctx;
    JSValue proto = JS_GetClassProto(ctx, VariantWrapClassID);

    JSValue obj = JS_NewObjectProtoClass(ctx, proto, VariantWrapClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;


    JS_SetOpaque(obj, ref);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
};

static void VariantWrapFinalizer(JSRuntime *rt, JSValue val) {

};

static JSClassDef VariantWrapClass = {
    "VariantWrap",
    .finalizer = VariantWrapFinalizer,
};

void NativeVariantWrapInit (JSContext* ctx, JSValue ns) {
    JS_NewClassID(&VariantWrapClassID);
    JS_NewClass(JS_GetRuntime(ctx), VariantWrapClassID, &VariantWrapClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    JS_SetClassProto(ctx, VariantWrapClassID, proto);
    // JSValue obj = JS_NewCFunction2(ctx, ViewConstructor, "VariantWrap", 1, JS_CFUNC_constructor, 0);
    // JS_SetConstructor(ctx, obj, proto);
    // JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
};

