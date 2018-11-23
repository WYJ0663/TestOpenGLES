#include <EGL/egl.h>
#include <android/native_window_jni.h>

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

EGLBoolean eglOpen(EGLContexts *eglContexts);

EGLBoolean linkWindow(EGLContexts *eglContexts);

void display(EGLContexts *eglContexts);

void getWindow(EGLContexts *eglContexts, JNIEnv *env, jobject surface);

EGLBoolean setWindowBuffersGeometry(EGLContexts *eglContexts, int32_t width, int32_t height);

int eglDestroye(EGLContexts *eglContexts);