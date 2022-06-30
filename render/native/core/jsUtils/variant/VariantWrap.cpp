#include "VariantWrap.hpp"

static JSClassID VariantWrapClassID;

static JSValue NativeVariantToString(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    QVariant* ref = (QVariant*)JS_GetOpaque(this_val, VariantWrapClassID);
    QString str = ref->toString();
    QByteArray ba = str.toLocal8Bit();
    
    JSValue result = JS_NewStringLen(ctx, ba.data(), ba.size());

    return result;
};

static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    SJS_CFUNC_DEF("toString", 0, NativeVariantToString),  
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

JSValue VariantWrapper(QVariant* ref) {
    SJSRuntime* qrt;
    JSContext* ctx;

    qrt = GetSJSInstance();
    ctx = qrt->ctx;

    JSValue obj = JS_NewObjectClass(ctx, VariantWrapClassID);
    if (JS_IsException(obj))
        goto fail;


    JS_SetOpaque(obj, ref);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
};

static void VariantWrapFinalizer(JSRuntime *rt, JSValue val) {
    QVariant *ref = (QVariant *)JS_GetOpaque(val, VariantWrapClassID);
    if (ref) {
        free(ref);
    }
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

