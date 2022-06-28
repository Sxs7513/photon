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

#include "core/jsUtils/event/click/Click.h"

bool FireEventToJS(QEvent* event = nullptr, const char* uid = nullptr, std::string eventType = nullptr);

void NativeEventWrapInit (JSContext* ctx);

typedef JSValue (*wrapFunc)(QEvent* e);

static std::map<std::string, wrapFunc> WrapEventDict {
    { "click", &WrapClickEvent }
};