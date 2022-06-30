#include "Event.h"

bool FireEventToJS(QEvent* event, QString uid, std::string eventType, QObject* eventTarget) {
    SJSRuntime* qrt;
    JSValue arg[3];
    JSContext* ctx;

    qrt = GetSJSInstance();
    ctx = qrt->ctx;
    std::map<std::string, wrapFunc>::iterator iter = WrapEventDict.find(eventType);

    if (iter != WrapEventDict.end()) {
        wrapFunc func = iter->second;
        QByteArray ba = uid.toLocal8Bit();
        char* uidstr = ba.data();

        arg[0] = JS_NewStringLen(ctx, uidstr, ba.size());
        arg[1] = JS_NewString(ctx, eventType.data());
        arg[2] = func(event, eventTarget);

        JSValue globalObj = JS_GetGlobalObject(ctx);
        JSValue fire = JS_GetPropertyStr(ctx, globalObj, "FIRE_QEVENT_CALLBACK");
        JSValue ret = JS_Call(ctx, fire, JS_NULL, 3, arg);
        JS_FreeValue(ctx, globalObj);
        JS_FreeValue(ctx, fire);
        JS_FreeValue(ctx, ret);
        JS_FreeValue(ctx, arg[0]);
        JS_FreeValue(ctx, arg[1]);
        JS_FreeValue(ctx, arg[2]);

        if (event != nullptr) {
            return event->isAccepted();
        } else {
            return true;
        }
    }

    return true;
}

void NativeEventWrapInit (JSContext* ctx) {
    NativeClickEventWrapInit(ctx);
    NativeTextChangeEventWrapInit(ctx);
}
