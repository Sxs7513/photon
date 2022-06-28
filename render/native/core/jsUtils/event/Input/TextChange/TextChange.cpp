#include "Click.h"

#include <stdlib.h>

typedef struct EVENT_REF {
    int test;
    QEvent* e;
} EVENT_REF;

static JSClassID WrapTextChangeID;

static void EventFinalizer(JSRuntime *rt, JSValue val) {
    EVENT_REF *th = (EVENT_REF *)JS_GetOpaque(val, WrapTextChangeID);
    if (th) {
        free(th);
    }
}

static JSClassDef ClickEventWrapClass = {
    "event",
    .finalizer = EventFinalizer,
};

JSValue WrapClickEvent (QEvent* e) {
    SJSRuntime* qrt;
    JSContext* ctx;
    JSValue proto;
    JSValue obj;
    EVENT_REF* s;

    qrt = GetSJSInstance();
    ctx = qrt->ctx;
    proto = JS_GetClassProto(ctx, WrapTextChangeID);
    obj = JS_NewObjectProtoClass(ctx, proto, WrapTextChangeID);
    JS_FreeValue(ctx, proto);
    s = (EVENT_REF*)js_mallocz(ctx, sizeof(*s));

    s->e = e;

    JS_SetOpaque(obj, s);

    return obj;
};

static JSValue NativeEventStopPropagation(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    EVENT_REF* ref = (EVENT_REF*)JS_GetOpaque(this_val, WrapTextChangeID);
    if (ref) {
        QEvent* e = ref->e;
        e->accept();
    }
};

static const JSCFunctionListEntry component_proto_funcs[] = {
    SJS_CFUNC_DEF("stopPropagation", 0, NativeEventStopPropagation),
};

void NativeTextChangeEventWrapInit (JSContext* ctx) {
    JS_NewClassID(&WrapTextChangeID);
    JS_NewClass(JS_GetRuntime(ctx), WrapTextChangeID, &ClickEventWrapClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, component_proto_funcs, countof(component_proto_funcs));
    JS_SetClassProto(ctx, WrapTextChangeID, proto);
}