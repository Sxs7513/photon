#pragma once

extern "C" {
    #include "quickjs-libc.h"
    #include <sjs.h>
}

#include <QEvent>
#include <QWidget>

#include "engine.hpp"
#include "core/JSUtils/Event/Event.h"

void NativeClickEventWrapInit (JSContext* ctx);

JSValue WrapClickEvent (QEvent* e = nullptr, QObject* eventTarget = nullptr);