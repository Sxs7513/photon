#include "Components.h"

#define NATIVE_COMPONENT "NativeComponents"

void NativeComponentInit (JSContext* ctx, JSValue ns) {
    JSValue component_obj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, ns, NATIVE_COMPONENT, component_obj);

    NativeComponentViewInit(ctx, component_obj);
    NativeComponentContainerInit(ctx, component_obj);
    // native_component_flexLayout_init(ctx, component_obj);
    NativeComponentTextInit(ctx, component_obj);
    NativeComponentButtonInit(ctx, component_obj);
    NativeComponentImageInit(ctx, component_obj);
    NativeComponentScrollViewInit(ctx, component_obj);

    NativeLoadingInit(ctx, component_obj);
}