#include <EGL/egl.h>

typedef struct EGLContexts {
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLContext eglContext;
    EGLint eglFormat;//颜色格式

    EGLConfig config;
    ANativeWindow *window;

    int width;
    int height;
} EGLContexts;