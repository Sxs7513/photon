#pragma once

extern "C" {
    #include "quickjs-libc.h"
    #include "sjs.h"
}

#include <map>
#include <stdlib.h>

#include <QEvent>
#include <QDebug>

#include "engine.hpp"

typedef struct EVENT_REF {
    int test;
    QEvent* e;
} EVENT_REF;

bool FireEventToJS(QEvent* event = nullptr, const char* uid = nullptr, std::string eventType = nullptr, QObject* eventTarget = nullptr);

void NativeEventWrapInit (JSContext* ctx);

typedef JSValue (*wrapFunc)(QEvent* e);

static std::map<std::string, wrapFunc> WrapEventDict {
    { "click", &WrapClickEvent }
};

#define WRAPPED_EVENT_METHODS
    static JSValue NativeEventStopPropagation(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
        EVENT_REF* ref = (EVENT_REF*)JS_GetOpaque(this_val, WrapClickEventID);
        if (ref) {
            QEvent* e = ref->e;
            e->accept();
        }
    };

#define WRAPPED_JS_METHODS_REGISTER
    SJS_CFUNC_DEF("stopPropagation", 0, NativeEventStopPropagation),