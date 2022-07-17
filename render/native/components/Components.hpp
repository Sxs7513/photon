#pragma once

#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "quickjs-libc.h"
    #include <sjs.h>
    #include <jsapi.h>
};

#include <QtCore/QObject>
#include <QVariant>

#include "core/JSUtils/variant/VariantWrap.hpp"

typedef struct COMP_REF {
    void* comp;
    const char* uid;
} COMP_REF;

void NativeComponentViewInit (JSContext* ctx, JSValue ns);

void NativeComponentContainerInit (JSContext* ctx, JSValue ns);

void NativeComponentInit (JSContext* ctx, JSValue ns);

// void native_component_flexLayout_init (JSContext* ctx, JSValue ns);

void NativeComponentTextInit (JSContext* ctx, JSValue ns);

void NativeComponentButtonInit (JSContext* ctx, JSValue ns);

void NativeComponentImageInit (JSContext* ctx, JSValue ns);

void NativeLoadingInit (JSContext* ctx, JSValue ns);

void NativeComponentScrollViewInit (JSContext* ctx, JSValue ns);

void NativeComponentInputInit (JSContext* ctx, JSValue ns);

#define WRAPPED_JS_METHODS(COMPONENT,COMPONENT_NAME)                                                                        \
    static JSValue NativeCompShow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {                    \
        COMP_REF* s = (COMP_REF*)JS_GetOpaque3(this_val);                                                                   \
        printf("%s %s show\n", COMPONENT_NAME, s->uid);                                                                     \
        ((COMPONENT*)(s->comp))->show();                                                                                    \
    };                                                                                                                      \
                                                                                                                            \
    static JSValue NativeCompSetStyle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {                \
        if (argc >= 1 && JS_IsString(argv[0])) {                                                                            \
            const char* style = JS_ToCString(ctx, argv[0]);                                                                 \
            JS_FreeValue(ctx, argv[0]);                                                                                     \
            COMP_REF* s = (COMP_REF*)JS_GetOpaque3(this_val);                                                               \
            QString currentStyleSheet = ((COMPONENT*)(s->comp))->styleSheet();                                              \
            QString newStyle = QString(style);                                                                              \
            if (currentStyleSheet != newStyle) {                                                                            \
                ((COMPONENT*)(s->comp))->setStyleSheet(newStyle);                                                           \
                printf("%s %s setStyle\n", COMPONENT_NAME, s->uid);                                                         \
            }                                                                                                               \
        }                                                                                                                   \
    }                                                                                                                       \
    static JSValue NativeCompClose(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {                   \
        COMP_REF* s = (COMP_REF*)JS_GetOpaque3(this_val);                                                                   \
        printf("%s %s close\n", COMPONENT_NAME, s->uid);                                                                    \
        ((COMPONENT*)(s->comp))->close();                                                                                   \
    }                                                                                                                       \
    static JSValue NativeCompSetMinimumSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {          \
        if (argc >= 2 && JS_IsNumber(argv[0]) && JS_IsNumber(argv[1])) {                                                    \
            int width;                                                                                                      \
            int height;                                                                                                     \
                                                                                                                            \
            JS_ToInt32(ctx, &width, argv[0]);                                                                               \
            JS_ToInt32(ctx, &height, argv[1]);                                                                              \
                                                                                                                            \
            COMP_REF* s = (COMP_REF*)JS_GetOpaque3(this_val);                                                               \
            ((COMPONENT*)(s->comp))->setMinimumSize(width, height);                                                         \
            printf("%s %s setMinimumSize\n", COMPONENT_NAME, s->uid);                                                       \
        }                                                                                                                   \
    }                                                                                                                       \
    static JSValue NativeCompSetMaximumSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {          \
        if (argc >= 2 && JS_IsNumber(argv[0]) && JS_IsNumber(argv[1])) {                                                    \
            int width;                                                                                                      \
            int height;                                                                                                     \
                                                                                                                            \
            JS_ToInt32(ctx, &width, argv[0]);                                                                               \
            JS_ToInt32(ctx, &height, argv[1]);                                                                              \
                                                                                                                            \
            COMP_REF* s = (COMP_REF*)JS_GetOpaque3(this_val);                                                               \
            ((COMPONENT*)(s->comp))->setMaximumSize(width, height);                                                         \
            printf("%s %s setMaximumSize\n", COMPONENT_NAME, s->uid);                                                       \
        }                                                                                                                   \
    }                                                                                                                       \
    static JSValue NativeCompGetFlexNode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {             \
        COMP_REF* s = (COMP_REF*)JS_GetOpaque3(this_val);                                                                   \
        void* node = (void *)(((COMPONENT*)(s->comp))->getFlexNode());                                                      \
        JSValue obj = JS_NewObject(ctx);                                                                                    \
        JS_SetOpaque(obj, node);                                                                                            \
        return obj;                                                                                                         \
    }                                                                                                                       \
    static JSValue NativeCompAddEventListener(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {        \
        if (argc >= 1 && JS_IsString(argv[0])) {                                                                            \
            COMP_REF* s = (COMP_REF*)JS_GetOpaque3(this_val);                                                               \
            size_t len;                                                                                                     \
            const char* eventType = JS_ToCStringLen(ctx, &len, argv[0]);                                                    \
            std::string str(eventType, 0, len);                                                                             \
            ((COMPONENT*)(s->comp))->addEventListener(str);                                                                 \
            JS_FreeCString(ctx, eventType);                                                                                 \
            return JS_NewBool(ctx, 1);                                                                                           \
        }                                                                                                                   \
        return JS_NewBool(ctx, 0);                                                                                               \    
    }                                                                                                                       \
                                                                                                                            \
    static JSValue NativeCompProperty(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {                \
        if (argc >= 1 && JS_IsString(argv[0])) {                                                                            \
            COMP_REF* s = (COMP_REF*)JS_GetOpaque3(this_val);                                                               \
            const char* property = JS_ToCString(ctx, argv[0]);                                                              \
            QVariant* ref = new QVariant(((QWidget*)(s->comp))->property(property));                                        \
            JS_FreeCString(ctx, property);                                                                                 \
            JSValue obj = VariantWrapper(ref);                                                                              \
            return obj;                                                                                                     \
        }                                                                                                                   \
    }                                                                                                                       \
                                                                                                                            \

#define WRAPPED_JS_METHODS_REGISTER                                                                       \
    SJS_CFUNC_DEF("show", 0, NativeCompShow),                                                             \
    SJS_CFUNC_DEF("setStyle", 0, NativeCompSetStyle),                                                     \
    SJS_CFUNC_DEF("close", 0, NativeCompClose),                                                           \
    SJS_CFUNC_DEF("setMinimumSize", 0, NativeCompSetMinimumSize),                                         \
    SJS_CFUNC_DEF("setMaximumSize", 0, NativeCompSetMaximumSize),                                         \
    SJS_CFUNC_DEF("getFlexNode", 0, NativeCompGetFlexNode),                                               \
    SJS_CFUNC_DEF("addEventListener", 0, NativeCompAddEventListener),                                     \
    SJS_CFUNC_DEF("property", 0, NativeCompProperty),                                                     \
                                                                                                          \

void QStringToChar(QString source, char** dst);
