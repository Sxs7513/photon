#include "TextChange.hpp"

static JSClassID WrapTextChangeEventID;

static void EventFinalizer(JSRuntime *rt, JSValue val) {
    EVENT_REF *th = (EVENT_REF *)JS_GetOpaque(val, WrapTextChangeEventID);
    if (th) {
        free(th);
    }
};

static JSClassDef TextChangeEventWrapClass = {
    "event",
    .finalizer = EventFinalizer,
};

JSValue WrapTextChangeEvent (QEvent* e, QObject* eventTarget) {
    SJSRuntime* qrt;
    JSContext* ctx;
    JSValue proto;
    JSValue obj;
    QString valueString;
    char* value;

    qrt = GetSJSInstance();
    ctx = qrt->ctx;
    proto = JS_GetClassProto(ctx, WrapTextChangeEventID);
    obj = JS_NewObjectProtoClass(ctx, proto, WrapTextChangeEventID);
    JS_FreeValue(ctx, proto);

    bool isQTextEdit = eventTarget->metaObject()->className() == QStringLiteral("SInput");
    bool isQLineEdit = eventTarget->metaObject()->className() == QStringLiteral("SLineEdit");
    
    if (isQTextEdit) {
        valueString = ((SInput*)eventTarget)->property("plainText").toString();
    } else if (isQLineEdit) {
        // valueString = ((SLineEdit*)eventTarget)->property("text").toString();
    }

    value = valueString.toLocal8Bit().data();

    JS_SetPropertyStr(ctx, obj, "value", JS_NewString(ctx, value));

    return obj;
};

static const JSCFunctionListEntry component_proto_funcs[] = {

};

void NativeTextChangeEventWrapInit (JSContext* ctx) {
    JS_NewClassID(&WrapTextChangeEventID);
    JS_NewClass(JS_GetRuntime(ctx), WrapTextChangeEventID, &TextChangeEventWrapClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, component_proto_funcs, countof(component_proto_funcs));
    JS_SetClassProto(ctx, WrapTextChangeEventID, proto);
};