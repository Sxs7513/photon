extern "C" {
    #include "quickjs-libc.h"
    #include <sjs.h>
}

#include "engine.hpp"

#include <QVariant>
#include <QString>

JSValue VariantWrapper(QVariant* target);

void NativeVariantWrapInit (JSContext* ctx, JSValue ns);