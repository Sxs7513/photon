#include "ScrollView.hpp"

static JSClassID ScrollViewClassID;

WRAPPED_JS_METHODS(SScrollArea, "ScrollView")

static JSValue NativeCompInsertChildBefore(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 2 && JS_IsObject(argv[0]) && JS_IsObject(argv[1])) {
        COMP_REF* beforeChild = (COMP_REF*)JS_GetOpaque3(argv[0]);
        COMP_REF* child = (COMP_REF*)JS_GetOpaque3(argv[0]);
        COMP_REF* parent = (COMP_REF*)JS_GetOpaque(this_val, ScrollViewClassID);

        JSAtom flexNodeAtom = JS_NewAtom(ctx, "getFlexNode");
        JSValue beforeChildFlexNode = JS_Invoke(ctx, argv[0], flexNodeAtom, 0, NULL);
        JSValue childFlexNode = JS_Invoke(ctx, argv[1], flexNodeAtom, 0, NULL);
        
        qDebug("ScrollView %s insertChild %s %s", parent->uid, child->uid, beforeChild->uid);
        ((SScrollArea*)(parent->comp))->insertChildBefore((void*)(child->comp), JS_GetOpaque3(beforeChildFlexNode), JS_GetOpaque3(childFlexNode));
        JS_FreeValue(ctx, childFlexNode);
        JS_FreeValue(ctx, beforeChildFlexNode);
        JS_FreeAtom(ctx, flexNodeAtom);
    }
    return JS_UNDEFINED;
};

static JSValue NativeCompRemoveChild(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsObject(argv[0])) {
        COMP_REF* child = (COMP_REF*)JS_GetOpaque3(argv[0]);
        COMP_REF* parent = (COMP_REF*)JS_GetOpaque(this_val, ScrollViewClassID);

        JSAtom flexNodeAtom = JS_NewAtom(ctx, "getFlexNode");
        JSValue childFlexNode = JS_Invoke(ctx, argv[0], flexNodeAtom, 0, NULL);
        
        qDebug("ScrollView %s remove child %s", parent->uid, child->uid);
        ((SScrollArea*)(parent->comp))->removeChild((void*)(child->comp), JS_GetOpaque3(childFlexNode));
        JS_FreeValue(ctx, childFlexNode);
        JS_FreeAtom(ctx, flexNodeAtom);
    }
    return JS_UNDEFINED;
};

static JSValue NativeCompAppendChild(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsObject(argv[0])) {
        COMP_REF* child = (COMP_REF*)JS_GetOpaque3(argv[0]);
        COMP_REF* parent = (COMP_REF*)JS_GetOpaque(this_val, ScrollViewClassID);
        
        JSAtom flexNodeAtom = JS_NewAtom(ctx, "getFlexNode");
        JSValue childFlexNode = JS_Invoke(ctx, argv[0], flexNodeAtom, 0, NULL);

        qDebug("ScrollView %s append child %s", parent->uid, child->uid);
        ((SScrollArea*)(parent->comp))->appendChild((void*)(child->comp), JS_GetOpaque3(childFlexNode));
        JS_FreeValue(ctx, childFlexNode);
        JS_FreeAtom(ctx, flexNodeAtom);
    }
    return JS_UNDEFINED;
};

static JSValue NativeCompSetFlexNodeSizeControlled(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (JS_IsBool(argv[0])) {
        COMP_REF* s = (COMP_REF*)JS_GetOpaque(this_val, ScrollViewClassID);
        bool isSizeControlled = (bool)JS_ToBool(ctx, argv[0]);
        ((SScrollArea*)(s->comp))->setFlexNodeSizeControlled(isSizeControlled);
    }
};

// static JSValue NativeCompAddWidget(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
//     COMP_REF* s = (COMP_REF*)JS_GetOpaque(this_val, ScrollViewClassID);
//     ((SScrollArea*)(s->comp))->setWidget(((SScrollArea*)(s->comp))->root);
// };

static JSValue NativeCompSetHorizontalEnable(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (JS_IsBool(argv[0])) {
        bool payload = (bool)JS_ToBool(ctx, argv[0]);
        COMP_REF* s = (COMP_REF*)JS_GetOpaque(this_val, ScrollViewClassID);
        ((SScrollArea*)(s->comp))->enableHorizontal(payload);
    }
};

static JSValue NativeCompSetVerticalEnable(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (JS_IsBool(argv[0])) {
        bool payload = (bool)JS_ToBool(ctx, argv[0]);
        COMP_REF* s = (COMP_REF*)JS_GetOpaque(this_val, ScrollViewClassID);
        ((SScrollArea*)(s->comp))->enableVertical(payload);
    }
};

static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    WRAPPED_JS_METHODS_REGISTER
    SJS_CFUNC_DEF("insertChildBefore", 0, NativeCompInsertChildBefore),
    SJS_CFUNC_DEF("removeChild", 0, NativeCompRemoveChild),
    SJS_CFUNC_DEF("appendChild", 0, NativeCompAppendChild),
    // SJS_CFUNC_DEF("addWidget", 0, NativeCompAddWidget),
    SJS_CFUNC_DEF("setHorizontalEnable", 0, NativeCompSetHorizontalEnable),
    SJS_CFUNC_DEF("setVerticalEnable", 0, NativeCompSetVerticalEnable),
    SJS_CFUNC_DEF("setFlexNodeSizeControlled", 0, NativeCompSetFlexNodeSizeControlled),
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

static JSValue ScrollViewConstructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
    JSValue proto;
    JSValue obj;
    JSValue arg;
    JSValue jsUid;
    const char* uid;

    COMP_REF *s;

    if (JS_IsObject(argv[0])) {
        arg = argv[0];
        jsUid = JS_GetPropertyStr(ctx, arg, "uid");
        if (JS_IsString(jsUid)) {
            uid = JS_ToCString(ctx, jsUid);
            JS_FreeValue(ctx, jsUid);
        }
    }

    if (JS_IsUndefined(new_target)) {
        proto = JS_GetClassProto(ctx, ScrollViewClassID);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, ScrollViewClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    s->uid = uid;
    s->comp = new SScrollArea();

    (static_cast<SScrollArea*>(s->comp))->setObjectName(QString(uid));
    JS_FreeCString(ctx, uid);

    if (!s)
        goto fail;

    JS_SetOpaque(obj, s);
    qDebug("view %s created", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
};

static void ViewFinalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, ScrollViewClassID);
    qDebug("scrollview %s release", th->uid);
    if (th) {
        free(th);
    }
};

static JSClassDef ScrollViewClass = {
    "scrollview",
    .finalizer = ViewFinalizer,
};

void NativeComponentScrollViewInit (JSContext* ctx, JSValue ns) {
    JS_NewClassID(&ScrollViewClassID);
    JS_NewClass(JS_GetRuntime(ctx), ScrollViewClassID, &ScrollViewClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    JS_SetClassProto(ctx, ScrollViewClassID, proto);

    JSValue obj = JS_NewCFunction2(ctx, ScrollViewConstructor, "ScrollView", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
    JS_DefinePropertyValueStr(ctx, ns, "ScrollView", obj, JS_PROP_C_W_E);
};

