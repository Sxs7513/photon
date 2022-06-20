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