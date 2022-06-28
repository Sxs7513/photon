extern "C" {
    #include "quickjs-libc.h"
    #include <sjs.h>
}

#include "engine.hpp"

#include <QVariant>

JSValue VariantWrapper(QVariant* target);