#pragma once

extern "C" {
    #include "quickjs-libc.h"
    #include "sjs.h"
}

#include <map>

#include <QEvent>
#include <QDebug>

#include "engineUtils.hpp"

#include "core/jsUtils/event/click/Click.h"

bool FireEventToJS(QEvent* event, const char* uid, std::string eventType);

void NativeEventWrapInit (JSContext* ctx);

typedef JSValue (*wrapFunc)(QEvent* e);

static std::map<std::string, wrapFunc> WrapEventDict {
    { "click", &WrapClickEvent }
};