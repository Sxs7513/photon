
#include "Loading.hpp"

typedef struct LoadingWaitWrap {
    JSContext *ctx;
    uv_timer_t req;
    SJSPromise result;
} LoadingWaitWrap;

static LoadingWaitWrap* lw = nullptr;

static void LoadingCallBack (uv_timer_t* handle) {
    JSContext* ctx;
    if (lw != nullptr) {
        ctx = lw->ctx;
        SLoading::hideLoading();
        uv_timer_stop(&lw->req);
        SJSSettlePromise(ctx, &lw->result, 0, 0, nullptr);
        free(lw);
        lw = nullptr;
    }
};

static JSValue ShowLoading(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    JSValue arg;
    JSValue duration = JS_UNDEFINED;
    JSValue text = JS_UNDEFINED;
    int64_t dura = 0;

    if (lw != nullptr) {
        return JS_UNDEFINED;
    }

    if (JS_IsObject(argv[0])) {
        arg = argv[0];
        duration = JS_GetPropertyStr(ctx, arg, "dutation");
        text = JS_GetPropertyStr(ctx, arg, "text");
    }
    if (JS_IsUndefined(duration)) {
        dura = 3000;
    } else {
        JS_ToInt64(ctx, &dura, duration);
    }

    lw = (LoadingWaitWrap*)malloc(sizeof(LoadingWaitWrap));
    lw->ctx = ctx;

    uv_timer_init(SJSGetLoop(ctx), &lw->req);
    uv_timer_start(&lw->req, &LoadingCallBack, dura, 0);
    SLoading::setText(JS_IsUndefined(text) ? "" : JS_ToCString(ctx, text));
    SLoading::showLoading();
    JS_FreeValue(ctx, duration);
    JS_FreeValue(ctx, text);

    return SJSInitPromise(ctx, &lw->result);
};

static JSValue HideLoading(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    LoadingCallBack(NULL);
    return JS_TRUE;
};

static const JSCFunctionListEntry loading[] = {
    SJS_CFUNC_DEF("showLoading", 1, ShowLoading ),
    SJS_CFUNC_DEF("hideLoading", 1, HideLoading ),
};

void NativeLoadingInit (JSContext* ctx, JSValue ns) {
    JSValue bridge = SJSGetJSBridge(ctx);
    JS_SetPropertyFunctionList(ctx, bridge, loading, countof(loading));
    JS_FreeValue(ctx, bridge);
};