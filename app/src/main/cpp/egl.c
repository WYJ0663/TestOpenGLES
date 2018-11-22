//
// Created by yijunwu on 2018/11/22.
//
#include <EGL/egl.h>
#include <android/native_window_jni.h>
#include "log.h"
#include "egl.h"


//Display → Config → Surface
EGLBoolean eglOpen(EGLContexts *eglContexts) {
    //get
    EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY) {
        LOGV("eglGetDisplay failure.");
        return EGL_FALSE;
    }
    const char *info = eglQueryString(eglDisplay, EGL_VENDOR);
    LOGV(" eglGetDisplay info %s", info);

    eglContexts->eglDisplay = eglDisplay;
    LOGV(" eglGetDisplay ok");

    //init
    EGLint majorVersion;
    EGLint minorVersion;
    EGLBoolean success = eglInitialize(eglDisplay, &majorVersion,
                                       &minorVersion);
    if (!success) {
        LOGV(" eglInitialize failure.");
        return EGL_FALSE;
    }
    LOGV(" eglInitialize ok");

    //config
    EGLint numConfigs;
    EGLConfig config;
    static const EGLint CONFIG_ATTRIBS[] = {EGL_BUFFER_SIZE, EGL_DONT_CARE,
                                            EGL_RED_SIZE, 5,
                                            EGL_GREEN_SIZE, 6,
                                            EGL_BLUE_SIZE, 5,
                                            EGL_DEPTH_SIZE, 16,
                                            EGL_ALPHA_SIZE, EGL_DONT_CARE,
                                            EGL_STENCIL_SIZE, EGL_DONT_CARE,
                                            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                                            EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE // the end
    };

    static const EGLint configAttribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };

    success = eglChooseConfig(eglDisplay, configAttribs, &config, 1,
                              &numConfigs);
    if (!success) {
        LOGV(" eglChooseConfig failure.");
        return EGL_FALSE;
    }
    eglContexts->config = config;
    LOGV(" eglChooseConfig ok");

    //create context
    const EGLint attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    EGLContext elgContext = eglCreateContext(eglDisplay, config, EGL_NO_CONTEXT,
                                             attribs);
    if (elgContext == EGL_NO_CONTEXT) {
        LOGV(" eglCreateContext failure, error is %d", eglGetError());
        return EGL_FALSE;
    }
    eglContexts->eglContext = elgContext;
    LOGV(" eglCreateContext ok");

    //config
    EGLint eglFormat;
    success = eglGetConfigAttrib(eglDisplay, config, EGL_NATIVE_VISUAL_ID,
                                 &eglFormat);
    if (!success) {
        LOGV(" eglGetConfigAttrib failure.");
        return EGL_FALSE;
    }
    eglContexts->eglFormat = eglFormat;
    LOGV(" eglGetConfigAttrib ok");


    return EGL_TRUE;
}

EGLBoolean linkWindow(EGLContexts *eglContexts) {

    EGLSurface eglSurface = eglCreateWindowSurface(eglContexts->eglDisplay, eglContexts->config,
                                                   eglContexts->window, 0);
    if (NULL == eglSurface) {
        LOGV(" eglCreateWindowSurface failure.");
        return EGL_FALSE;
    }
    eglContexts->eglSurface = eglSurface;
    LOGV(" eglCreateWindowSurface ok");

    //关联屏幕
    EGLBoolean is = eglMakeCurrent(eglContexts->eglDisplay, eglSurface, eglSurface, eglContexts->eglContext);
    if (!is) {
        return EGL_FALSE;
    }
    LOGV(" eglMakeCurrent ok");
    return EGL_TRUE;
}

void draw(EGLContexts *eglContexts) {
    eglSwapBuffers(eglContexts->eglDisplay, eglContexts->eglContext);
}

void getWindow(EGLContexts *eglContexts, JNIEnv *env, jobject surface) {
    if (eglContexts->window) {
        ANativeWindow_release(eglContexts->window);
        eglContexts->window = 0;
    }
    eglContexts->window = ANativeWindow_fromSurface(env, surface);

    linkWindow(eglContexts);
}

EGLBoolean setWindowBuffersGeometry(EGLContexts *eglContexts, int32_t width, int32_t height) {
    //int32_t format = WINDOW_FORMAT_RGB_565;
    eglContexts->width = width;
    eglContexts->height = height;

    if (eglContexts->window == 0) {
        LOGV("mANativeWindow is NULL.");
        return EGL_FALSE;
    }

    int32_t is = ANativeWindow_setBuffersGeometry(eglContexts->window, width, height, eglContexts->eglFormat);
    if (is == 0) {
        return EGL_TRUE;
    } else {
        return EGL_FALSE;
    }
}


int eglDestroye(EGLContexts *eglContexts) {
    EGLBoolean success = eglDestroySurface(eglContexts->eglDisplay,
                                           eglContexts->eglSurface);
    if (!success) {
        LOGV("eglDestroySurface failure.");
    }

    success = eglDestroyContext(eglContexts->eglDisplay,
                                eglContexts->eglContext);
    if (!success) {
        LOGV("eglDestroySurface failure.");
    }

    success = eglTerminate(eglContexts->eglDisplay);
    if (!success) {
        LOGV("eglDestroySurface failure.");
    }

    eglContexts->eglSurface = NULL;
    eglContexts->eglContext = NULL;
    eglContexts->eglDisplay = NULL;

    if (eglContexts->window) {
        ANativeWindow_release(eglContexts->window);
        eglContexts->window = 0;
    }

    return 0;
}
