#pragma once

extern "C" {
    #include "quickjs-libc.h"
    #include <sjs.h>
}

#include <QEvent>

#include "engine.hpp"

void NativeClickEventWrapInit (JSContext* ctx);

JSValue WrapClickEvent (QEvent* e);