#pragma once

extern "C" {
    #include "quickjs-libc.h"
    #include "sjs.h"
};

#include <map>
#include <stdlib.h>

#include <QEvent>
#include <QDebug>
#include <QString>

#include "engine.hpp"

typedef struct EVENT_REF {
    int test;
    QEvent* e;
} EVENT_REF;

bool FireEventToJS(QEvent* event, QString uid, std::string eventType, QObject* eventTarget);

void NativeEventWrapInit (JSContext* ctx);

void NativeClickEventWrapInit (JSContext* ctx);

JSValue WrapClickEvent (QEvent* e, QObject* eventTarget);

void NativeTextChangeEventWrapInit (JSContext* ctx);

JSValue WrapTextChangeEvent (QEvent* e = nullptr, QObject* eventTarget = nullptr);

typedef JSValue (*wrapFunc)(QEvent* e, QObject* eventTarget);

static std::map<std::string, wrapFunc> WrapEventDict {
    { "click", &WrapClickEvent },
    { "textChange", &WrapTextChangeEvent }
};

#define WRAPPED_EVENT_METHODS                                                                                                           \
    static JSValue NativeEventStopPropagation(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {                    \
        EVENT_REF* ref = (EVENT_REF*)JS_GetOpaque3(this_val);                                                                           \
        if (ref) {                                                                                                                      \
            QEvent* e = ref->e;                                                                                                         \
            e->accept();                                                                                                                \
        }                                                                                                                               \
    };                                                                                                                                  \
                                                                                                                                        \

#define WRAPPED_EVENT_METHODS_REGISTER                                                                                                  \
    SJS_CFUNC_DEF("stopPropagation", 0, NativeEventStopPropagation),                                                                    