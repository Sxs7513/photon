extern "C" {
    #include <jsapi.h>
    #include "quickjs-libc.h"
    #include <sjs.h>
    #include <uv.h>
};
#include "render.h"
#include "engine.hpp"

#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <QApplication>

#include "engineUtils.hpp"

SJSRuntime* qrt = nullptr;
uv_loop_t *loop;
QApplication* app;
bool SJSFreed = false;

void ProcessQEvents () {
    app->processEvents();
    // if (app->closingDown() == true) {
    // } else {
    //     SJS_FreeRuntime(qrt);
    // }
}

void FreeJSRuntime (int signal) {
    SJSDisableForeverLoop(qrt);
    // printf("JSThread Abort!\n");
    // if (SJSFreed) return;
    // SJS_FreeRuntime(qrt);
    // SJSFreed = true;
    // printf("SJSRuntime Free!\n");
}

SJSRuntime* GetSJSInstance () {
    if (qrt == nullptr) {
        SJSRunOptions options;

        SJSDefaultOptions(&options);

        qrt = SJSNewRuntimeOptions(&options);
    }
    
    return qrt;
}

void* StartJSRuntime (int argc, char *argv[]) {
    printf("js vm Start\n");\

    char* filePath = argv[1];

    SJSRuntime* qrt;

    qrt = GetSJSInstance();

    qrt->uv_loop_inject = &ProcessQEvents;

    qrt->foreverLoop = 1;

    NativeRenderInit(qrt->ctx);

    char* path = (char*)malloc(PATH_MAX);
    GetBundlePath(path);
    SJSBootStrapGlobals(qrt->ctx, path);
    free(path);

    // signal(SIGSEGV, FreeJSRuntime);
    signal(SIGINT, FreeJSRuntime);

    char* absolutePath = SetJSEntryPath(filePath);
    SJSRunMain(qrt, absolutePath);
    SJSRun(qrt);

    free(absolutePath);
    SJSFreeRuntime(qrt);
    SJSClearJSApi();
    printf("js vm End \n");
}

int main (int argc, char *argv[]) {
    app = new QApplication(argc, argv);
    StartJSRuntime(argc, argv);

    printf("program end\n");
}