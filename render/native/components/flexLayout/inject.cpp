#include <components/Components.h>
#include <components/flexLayout/FlexLayout.h>

#include <stdlib.h>

static JSClassID flexLayout_class_id;

static JSValue native_comp_appendChild(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsObject(argv[0])) {
        COMP_REF* child = (COMP_REF*)JS_GetOpaque3(argv[0]);
        COMP_REF* parent = (COMP_REF*)JS_GetOpaque(this_val, flexLayout_class_id);
        ((QHBoxLayout*)(parent->comp))->addWidget((QWidget*)(child->comp));
        printf("flexLayout %d append child \n", parent->uid);
    }
};

static JSValue native_comp_removeChild(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsObject(argv[0])) {
        COMP_REF* child = (COMP_REF*)JS_GetOpaque3(argv[0]);
        COMP_REF* parent = (COMP_REF*)JS_GetOpaque(this_val, flexLayout_class_id);
        ((QHBoxLayout*)(parent->comp))->removeWidget((QWidget*)(child->comp));
        printf("flexLayout %d append child \n", parent->uid);
    }
};

static const JSCFunctionListEntry component_proto_funcs[] = {
    SJS_CFUNC_DEF("appendChild", 0, native_comp_appendChild),
    SJS_CFUNC_DEF("removeChild", 0, native_comp_removeChild),
};

static const JSCFunctionListEntry component_class_funcs[] = {
};

static JSValue flexLayout_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
    JSValue proto;
    JSValue obj;
    JSValue arg;
    JSValue jsUid;
    int32_t uid;
    COMP_REF *s;

    if (JS_IsObject(argv[0])) {
        arg = argv[0];
        jsUid = JS_GetPropertyStr(ctx, arg, "uid");
        if (JS_IsNumber(jsUid)) {
            JS_ToInt32(ctx, &uid, jsUid);
            JS_FreeValue(ctx, jsUid);
        }
    }

    if (JS_IsUndefined(new_target)) {
        proto = JS_GetClassProto(ctx, flexLayout_class_id);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, flexLayout_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    s->uid = uid;
    s->comp = new FlexLayout();
    if (!s)
        goto fail;

    JS_SetOpaque(obj, s);
    printf("flexLayout %d created \n", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static void flexLayout_finalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, flexLayout_class_id);
    printf("flexLayout %d release\n", th->uid);
    if (th) {
        free(th);
    }
}

static JSClassDef view_class = {
    "flexLayout",
    .finalizer = flexLayout_finalizer,
};

void native_component_flexLayout_init (JSContext* ctx, JSValue ns) {
    JS_NewClassID(&flexLayout_class_id);
    JS_NewClass(JS_GetRuntime(ctx), flexLayout_class_id, &view_class);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, component_proto_funcs, countof(component_proto_funcs));
    JS_SetClassProto(ctx, flexLayout_class_id, proto);

    JSValue obj = JS_NewCFunction2(ctx, flexLayout_constructor, "FlexLayout", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, component_class_funcs, countof(component_class_funcs));
    JS_DefinePropertyValueStr(ctx, ns, "FlexLayout", obj, JS_PROP_C_W_E);
}