#include <sjs.h>
#include <jsapi.h>

#include <string.h>
#include <unistd.h>
#include <stdio.h>

static JSValue SJSEvalModule(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    char* content = JS_ToCString(ctx, argv[0]);
    char* fileName = JS_ToCString(ctx, argv[1]);
    JSValue func_val = JS_Eval(
        ctx,
        content,
        strlen(content),
        fileName,
        JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY
    );
    if (JS_IsException(func_val)) {
        SJSDumpError(ctx);
        goto done;
    }
    JSModuleSetImportMeta(ctx, func_val, FALSE);

    JSValue ret = JS_EvalFunction(ctx, func_val);

done:
    JS_FreeCString(ctx, content);
    JS_FreeCString(ctx, fileName);
    return JS_UNDEFINED;
};

void* SJSGetRuntimeOpaque (JSContext* ctx) {
    SJSRuntime* qrt = JS_GetContextOpaque(ctx);
    return qrt->user_opaque;
}

void* SJSSetRuntimeOpaque (SJSRuntime* qrt, void* data) {
    qrt->user_opaque = data;
}

static void UVStop(uv_async_t *handle) {
    SJSRuntime *qrt = handle->data;

    uv_stop(&qrt->loop);
}

#define SJS_DEFAULT_STACK_SIZE 1048576

BOOL COREJSAPI_INITED = FALSE;

static const JSCFunctionListEntry SJSNativeFunction[] = {
    SJS_CFUNC_DEF("__NativeEvalModule", 2, SJSEvalModule),
    // SJS_CFUNC_DEF("__NativeEvalFunction", 2, SJSEvalFunction),
};

BOOL SJSBootStrapCore (SJSRuntime* qrt) {
    if (!COREJSAPI_INITED) {
        JSValue global_obj = JS_GetGlobalObject(qrt->ctx);
        JSStdInit(qrt, global_obj);
        JSNetworkInit(qrt, global_obj);
        JSTimersInit(qrt, global_obj);
        JSXHRInit(qrt, global_obj);
        JSProcessInit(qrt, global_obj);
        JSInitOS(qrt, global_obj);
        JSFSInit(qrt, global_obj);
        COREJSAPI_INITED = TRUE;
        JS_SetPropertyFunctionList(qrt->ctx, global_obj, SJSNativeFunction, countof(SJSNativeFunction));
        JS_FreeValue(qrt->ctx, global_obj);
    }
}

void SJSDefaultOptions(SJSRunOptions *options) {
    static SJSRunOptions default_options = {
        .mem_limit = -1,
        .stack_size = SJS_DEFAULT_STACK_SIZE
    };

    memcpy(options, &default_options, sizeof(*options));
}

SJSRuntime* SJSNewRuntimeOptions(SJSRunOptions *options) {
    return SJSNewRuntimeInternal(FALSE, options);
}

SJSRuntime* SJSNewRuntimeInternal(BOOL is_worker, SJSRunOptions *options) {
    SJSRuntime *qrt = calloc(1, sizeof(*qrt));
    memcpy(&(qrt->options), options, sizeof(options));

    qrt->rt = JS_NewRuntime();
    qrt->ctx = JS_NewContext(qrt->rt);

    JS_SetRuntimeOpaque(qrt->rt, qrt);
    JS_SetContextOpaque(qrt->ctx, qrt);

    JS_SetModuleLoaderFunc(qrt->rt, JSModuleNormalizeName, SJSModuleLoader, qrt);

    /* Set memory limit */
    JS_SetMemoryLimit(qrt->rt, options->mem_limit);

    /* Set stack size */
    JS_SetMaxStackSize(qrt->rt, options->stack_size);

    /* Enable BigFloat and BigDecimal */
    JS_AddIntrinsicBigFloat(qrt->ctx);
    JS_AddIntrinsicBigDecimal(qrt->ctx);

    qrt->is_worker = is_worker;

    uv_loop_init(&qrt->loop);

    // uv_prepare_init(&qrt->loop, &qrt->jobs.prepare);
    // qrt->jobs.prepare.data = qrt;

    uv_idle_init(&qrt->loop, &qrt->jobs.idle);
    qrt->jobs.idle.data = qrt;

    // uv_check_init(&qrt->loop, &qrt->jobs.check);
    // qrt->jobs.check.data = qrt;

    // uv_async_init(&qrt->loop, &qrt->stop, uv__stop);
    // qrt->stop.data = qrt;

    SJSJSBridgeInit(qrt);

    SJSBootStrapCore(qrt);

    SJSJSApiInit(qrt);
    return qrt;
};

static char* SJSMakeEntryCommonJS (char* buf, size_t *pbuf_len, char* filePath) {
    strcat(buf, "(function () { __loadMainModule(\"");
    strcat(buf, filePath);
    strcat(buf, "\")})()");

    *pbuf_len = strlen(buf);
}

void SJSRunMain(SJSRuntime *qrt, const char *filePath) {
    size_t buf_len;
    char buf[1000]= {0};
    JSContext *ctx = qrt->ctx;

    if (filePath) {
        SJSBootstrap(ctx);

        // SJSMakeEntryCommonJS(buf, &buf_len, filePath);

        // JSValue globalObj = JS_GetGlobalObject(ctx);
        // JSValue requireFunc = JS_GetPropertyStr(ctx, globalObj, "require");
        // JSValue path = JS_NewString(ctx, filePath);
        // JSValue ret = JS_Call(ctx, requireFunc, JS_UNDEFINED, 1, (JSValueConst *) &path);

        // buf = js_load_file(ctx, &buf_len, filePath);
        // JSValue func_val = JS_Eval(qrt->ctx,
        //                     buf,
        //                     buf_len,
        //                     filePath,
        //                     JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);

        // JSModuleSetImportMeta(ctx, func_val, TRUE);

        // JSValue ret = JS_EvalFunction(ctx, func_val);
        
        // if (JS_IsException(ret)) {
        //     SJSDumpError(ctx);
        // }

        // JS_FreeValue(ctx, ret);
    }
}

BOOL SJSFreeRuntime(SJSRuntime* qrt) {
    if (qrt->foreverLoop) {
        uv_unref((uv_handle_t *) &qrt->jobs.idle);
    }

    // uv_close((uv_handle_t *) &qrt->jobs.prepare, NULL);
    uv_idle_stop((uv_handle_t *) &qrt->jobs.idle);
    // uv_close((uv_handle_t *) &qrt->jobs.check, NULL);
    // uv_close((uv_handle_t *) &qrt->stop, NULL);
    
    JS_FreeContext(qrt->ctx);
    JS_FreeRuntime(qrt->rt);

    int closed = 0;
    for (int i = 0; i < 5; i++) {
        if (uv_loop_close(&qrt->loop) == 0) {
            closed = 1;
            break;
        }
        uv_run(&qrt->loop, UV_RUN_NOWAIT);
    }

    free(qrt);
}

static void UVIdleCb(uv_idle_t *handle) {
    SJSRuntime *qrt = handle->data;

    if (qrt->uv_loop_inject) {
        qrt->uv_loop_inject();
    }

    SJSExecuteJobs(qrt->ctx);

}

static void UVMaybeIdle(SJSRuntime *qrt) {
    if (JS_IsJobPending(qrt->rt))
        uv_idle_start(&qrt->jobs.idle, UVIdleCb);
    else
        uv_idle_stop(&qrt->jobs.idle);
}

void SJSExecuteJobs(JSContext *ctx) {
    JSContext *ctx1;
    int err;

    for (;;) {
        err = JS_ExecutePendingJob(JS_GetRuntime(ctx), &ctx1);
        if (err <= 0) {
            if (err < 0) {
                SJSDumpError(ctx1);
            }
            break;
        }
    }
}

static void UVCheckCb(uv_check_t *handle) {
    SJSRuntime *qrt = handle->data;

    SJSExecuteJobs(qrt->ctx);

    // UVMaybeIdle(qrt);
}

static void UVPrepareCb(uv_prepare_t *handle) {
    SJSRuntime *qrt = handle->data;

    if (qrt->uv_loop_inject) {
        qrt->uv_loop_inject();
    }

    UVMaybeIdle(qrt);
}

BOOL SJSDisableForeverLoop (SJSRuntime *qrt) {
    uv_unref((uv_handle_t *) &qrt->jobs.idle);
}

BOOL SJSRun(SJSRuntime *qrt) {
    uv_idle_start(&qrt->jobs.idle, UVIdleCb);
    // uv_prepare_start(&qrt->jobs.prepare, UVPrepareCb);
    // uv_unref((uv_handle_t *) &qrt->jobs.prepare);
    // uv_check_start(&qrt->jobs.check, UVCheckCb);

    if (!qrt->foreverLoop) {
        uv_unref((uv_handle_t *) &qrt->jobs.idle);
    }

    uv_run(&qrt->loop, UV_RUN_DEFAULT);

    int ret = 0;
    JSValue exc = JS_GetException(qrt->ctx);
    if (!JS_IsNull(exc)) {
        SJSDumpError1(qrt->ctx, exc);
        ret = 1;
    }

    JS_FreeValue(qrt->ctx, exc);

    return ret;
}