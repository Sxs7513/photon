extern "C" {
    #include <jsapi.h>
    #include "quickjs-libc.h"
    #include <sjs.h>
    #include <uv.h>
};
#include <render.h>

#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

SJSRuntime* qrt;
uv_loop_t *loop;
uv_timer_t fake_job_req;
pthread_t id;

JSValue js_console_something(JSContext *ctx, int argc, JSValueConst *argv) {
    JSValue global = JS_GetGlobalObject(ctx);
    JSValue callback = JS_GetPropertyStr(ctx, global, "a");
    JS_Call(ctx, callback, JS_NULL, argc, argv);
    JS_FreeValue(ctx, global);
    JS_FreeValue(ctx, callback);
}

void mock_native_call_js () {
    JSContext *ctx = qrt->ctx;
    JSValue arg = JS_NewInt32(ctx, 1000);
    int err = JS_EnqueueJob(ctx, js_console_something, 1, &arg);
    if (err != 0) {
        printf("enqueue fail");
    }
}

void free_JSRuntime (int signal) {
    printf("JSThread Abort!\n");
    SJSFreeRuntime(qrt);
    // uv_unref((uv_handle_t *) &qrt->loop);
    // uv_stop(&qrt->loop);
}

void* start_JSRuntime (void *arg) {
    printf("JSThread Start\n");

    SJSRunOptions options;

    SJSDefaultOptions(&options);

    qrt = SJSNewRuntimeOptions(&options);

    NativeRenderInit(qrt->ctx);
    char buf[100];
    memset(buf, 0, 100);
    getcwd(buf, 100);
    const char* bundle = "/bundle.js";
    strcat(buf, bundle);
    SJSBootStrapGlobals(qrt->ctx, buf);

    // signal(SIGKILL, free_JSRuntime);
    signal(SIGINT, free_JSRuntime);

    // const char *filepath = "/mnt/hgfs/kaifaban/jsengine/test/test1.js";
    const char *filepath = "/mnt/hgfs/kaifaban/jsengine/debug/test-render.js";
    SJSRunMain(qrt, filepath);
    
    SJSRun(qrt, 0);
    SJSFreeRuntime(qrt);
    SJSClearJSApi();
    printf("JSThread End \n");
}

void kill_JSThread () {
    pthread_kill(id, SIGINT);
}

int main () {
    int ret = pthread_create(&id, NULL, &start_JSRuntime, NULL);
    if (ret != 0) {
        printf("Create JSThread error!\n");
        exit(1);
    }

    loop = uv_default_loop();
    uv_timer_init(loop, &fake_job_req);
    // uv_timer_start(&fake_job_req, mock_native_call_js, 2000, 0);
    // uv_timer_start(&fake_job_req, kill_JSThread, 2000, 0);
    uv_run(loop, UV_RUN_DEFAULT);

    pthread_join(id, NULL);
    printf("program end\n");
}