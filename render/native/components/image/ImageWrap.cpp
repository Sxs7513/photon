#include "Image.h"

static JSClassID ImageClassID;

WRAPPED_JS_METHODS(SImage, "image")

static JSValue native_comp_setImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsString(argv[0])) {
        const char* url = JS_ToCString(ctx, argv[0]);
        QImage *img = new QImage;
        // char* path = (char*)malloc(PATH_MAX);
        // GetJSAssetsPath(path, url);
        img->load(url);
        // free(path);
        JS_FreeValue(ctx, argv[0]);

        COMP_REF* s = (COMP_REF*)JS_GetOpaque(this_val, ImageClassID);
        ((SImage*)(s->comp))->setPixmap(QPixmap::fromImage(*img));
        printf("image %s setImage \n", s->uid);
    }
};

static JSValue native_comp_setScaleContent(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc >= 1 && JS_IsBool(argv[0])) {
        bool scale = JS_ToBool(ctx, argv[0]);
        COMP_REF* s = (COMP_REF*)JS_GetOpaque(this_val, ImageClassID);
        ((SImage*)(s->comp))->setScaledContents(scale);
        printf("image %s setScaleContent \n", s->uid);
    }
};

static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    WRAPPED_JS_METHODS_REGISTER
    SJS_CFUNC_DEF("setImage", 0, native_comp_setImage),
    SJS_CFUNC_DEF("setScaleContent", 0, native_comp_setScaleContent),
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

static JSValue ImageConstructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv) {
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
        proto = JS_GetClassProto(ctx, ImageClassID);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, ImageClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    s->uid = uid;
    s->comp = new SImage();
    (static_cast<SImage*>(s->comp))->setObjectName(QString(uid));
    JS_FreeCString(ctx, uid);
    
    if (!s)
        goto fail;

    JS_SetOpaque(obj, s);
    printf("image %s created \n", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static void FlexLayoutFinalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, ImageClassID);
    printf("image %s release \n", th->uid);
    if (th) {
        free(th);
    }
}

static JSClassDef ViewClass = {
    "image",
    .finalizer = FlexLayoutFinalizer,
};

void NativeComponentImageInit (JSContext* ctx, JSValue ns) {
    JS_NewClassID(&ImageClassID);
    JS_NewClass(JS_GetRuntime(ctx), ImageClassID, &ViewClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    JS_SetClassProto(ctx, ImageClassID, proto);

    JSValue obj = JS_NewCFunction2(ctx, ImageConstructor, "Image", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
    JS_DefinePropertyValueStr(ctx, ns, "Image", obj, JS_PROP_C_W_E);
}