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

#include <QApplication>

SJSRuntime* qrt;
uv_loop_t *loop;
QApplication* app;
bool SJSFreed = false;

void process_QEvents () {
    app->processEvents();
    // if (app->closingDown() == true) {
    // } else {
    //     SJS_FreeRuntime(qrt);
    // }
}

void free_JSRuntime (int signal) {
    SJSDisableForeverLoop(qrt);
    // printf("JSThread Abort!\n");
    // if (SJSFreed) return;
    // SJS_FreeRuntime(qrt);
    // SJSFreed = true;
    // printf("SJSRuntime Free!\n");
}

void* start_JSRuntime () {
    printf("js vm Start\n");

    SJSRunOptions options;

    SJSDefaultOptions(&options);

    qrt = SJSNewRuntimeOptions(&options);

    qrt->uv_loop_inject = &process_QEvents;

    qrt->foreverLoop = 1;

    NativeRenderInit(qrt->ctx);
    char buf[100];
    memset(buf, 0, 100);
    getcwd(buf, 100);
    const char* bundle = "/bundle.js";
    strcat(buf, bundle);
    SJSBootStrapGlobals(qrt->ctx, buf);

    // signal(SIGSEGV, free_JSRuntime);
    signal(SIGINT, free_JSRuntime);

    const char *filepath = "/mnt/hgfs/kaifaban/jsengine/debug/test-render.js";
    SJSRunMain(qrt, filepath);
    
    SJSRun(qrt);

    SJSFreeRuntime(qrt);
    SJSClearJSApi();
    printf("js vm End \n");
}

int main (int argc, char *argv[]) {
    app = new QApplication(argc, argv);
    start_JSRuntime();

    printf("program end\n");
}