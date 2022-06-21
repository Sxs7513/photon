#include "sjs.h"
#include "utils.h"
#include <stdlib.h>

void SJSBootStrapGlobals(JSContext *ctx, char *filepath) {
    uint8_t *buf;
    size_t buf_len;
    buf = js_load_file(ctx, &buf_len, filepath);
    JSValue val = JS_Eval(ctx, buf, buf_len, filepath, JS_EVAL_TYPE_GLOBAL | JS_EVAL_FLAG_COMPILE_ONLY);

    JSModuleSetImportMeta(ctx, val, TRUE);

    JSValue ret = JS_EvalFunction(ctx, val);
    if (JS_IsException(ret)) {
        SJSDumpError(ctx);
    }

    JS_FreeValue(ctx, ret);
};

static void SJSWrapFunction (char* buf, char* content, size_t* pbuf_len, char** params, size_t paramsv) {
    strcat(buf, "(function (");
    int i;
    for (i = 0; i < paramsv; i++) {
        strcat(buf, params[i]);
        if (i != paramsv - 1) {
            strcat(buf, ",");
        }
    }
    strcat(buf, ") {");
    strcat(buf, content);
    strcat(buf, "})");

    *pbuf_len = strlen(buf);
}

static void SJSExecuteBootStrapper (JSContext* ctx, char* path, char** params, size_t paramsv, JSValue* argc, size_t argv) {
    char fullPath[PATH_MAX] = {0};
    size_t buflen;
    size_t newbuflen;

    GetProgramDir(fullPath);
    strcat(fullPath, SJSPATHSEP);
    strcat(fullPath, "lib");
    strcat(fullPath, SJSPATHSEP);
    strcat(fullPath, path);

    char* buf = js_load_file(ctx, &buflen, fullPath);
    char newbuf[buflen + 1000];
    newbuf[0] = '\0';
    SJSWrapFunction(newbuf, buf, &newbuflen, params, paramsv);

    JSValue func_val = JS_Eval(
        ctx,
        newbuf,
        newbuflen,
        path,
        JS_EVAL_TYPE_GLOBAL
    );
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JS_Call(ctx, func_val, globalObj, argc, argv);
    JS_FreeValue(ctx, globalObj);
    JS_FreeValue(ctx, func_val);
    free(buf);
};

void SJSBootstrap (JSContext* ctx) {
    SJSExecuteBootStrapper(ctx, "internal/bootstrap/loader.js", NULL, 0, NULL, 0);

    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue bootstrapLoader = JS_GetPropertyStr(ctx, globalObj, "NativeLoaderExports");
    JSValue requireFunc = JS_GetPropertyStr(ctx, bootstrapLoader, "require");
    JSValue NativeModule = JS_GetPropertyStr(ctx, bootstrapLoader, "NativeModule");

    JS_FreeValue(ctx, globalObj);
    JS_FreeValue(ctx, requireFunc);
    JS_FreeValue(ctx, NativeModule);
    JS_FreeValue(ctx, bootstrapLoader);
}