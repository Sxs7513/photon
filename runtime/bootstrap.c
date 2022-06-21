#include <sjs.h>

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

static void SJSWrapFunction (char* buf, char* content, size_t pbuf_len, char** params, size_t paramsv, JSValue* args, size_t argv) {
    strcat(buf, "(function (");
    int i;
    for (i = 0; i < paramsv; i++) {
        strcat[buf, params[i]];
        if (i != paramsv - 1) {
            strcat(buf, ",");
        }
    }
    strcat(buf, ") {");
    strcat(buf, content);
    strcat(buf, "})");

    *pbuf_len = strlen(buf);
}

static void SJSExecuteBootStrapper (JSContext* ctx, char* path, char** params, size_t paramsv, JSValue* args, size_t argv) {
    char fullPath[MAX_PATH] = {0};
    size_t buflen;
    size_t newbuflen;

    GetProgramDir(fullPath);
    strcat(fullPath, SJSPATHSEP);
    strcat(fullPath, "lib");
    strcat(fullPath, SJSPATHSEP);
    strcat(fullPath, path);

    char* buf = js_load_file(ctx, &buflen, fullPath);
    char newbuf[buflen + 1000] = {0};
    SJSWrapFunction(newbuf, buf, newbuflen, params, paramsv, paramsv, args);

    JSValue func_val = JS_Eval(
        qrt->ctx,
        newbuf,
        newbuflen,
        path,
    );

    JS_Call(ctx, )
};

void SJSBootstrap (JSContext* ctx) {
    char* loaderPath = "internal/bootstrap/loader.js"
    SJSExecuteBootStrapper(ctx, loaderPath, NULL, 0, NULL, 0);
}