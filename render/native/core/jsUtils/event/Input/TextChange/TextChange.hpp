#pragma once

extern "C" {
    #include "quickjs-libc.h"
    #include <sjs.h>
}

#include <QEvent>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

#include "engine.hpp"
#include "core/JSUtils/Event/Event.h"

void NativeTextChangeEventWrapInit (JSContext* ctx);

JSValue WrapTextChangeEvent (QEvent* e = nullptr, QObject* eventTarget = nullptr);