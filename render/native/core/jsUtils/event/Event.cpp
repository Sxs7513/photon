#include "Event.h"

#include <stdlib.h>

bool FireEventToJS(QEvent* event, const char* uid, std::string eventType) {
    SJSRuntime* qrt;
    JSValue arg[3];
    JSContext* ctx;

    qrt = GetSJSInstance();
    ctx = qrt->ctx;

    std::map<std::string, wrapFunc>::iterator iter = WrapEventDict.find(eventType);

    if (iter != WrapEventDict.end()) {
        wrapFunc func = iter->second;
        arg[0] = JS_NewString(ctx, uid);
        arg[1] = JS_NewString(ctx, eventType.data());
        arg[2] = func(event);

        JSValue globalObj = JS_GetGlobalObject(ctx);
        JSValue fire = JS_GetPropertyStr(ctx, globalObj, "FIRE_QEVENT_CALLBACK");
        JSValue ret = JS_Call(ctx, fire, JS_NULL, 3, arg);
        JS_FreeValue(ctx, globalObj);
        JS_FreeValue(ctx, fire);
        JS_FreeValue(ctx, ret);
        JS_FreeValue(ctx, arg[0]);
        JS_FreeValue(ctx, arg[1]);
        JS_FreeValue(ctx, arg[2]);

        return event->isAccepted();
    }
}

void NativeEventWrapInit (JSContext* ctx) {
    NativeClickEventWrapInit(ctx);
}
