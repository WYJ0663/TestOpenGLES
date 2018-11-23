#include <jni.h>
#include <malloc.h>
#include <pthread.h>

#include "egl.h"
#include "gles.h"
#include "log.h"

EGLContexts *eglContexts;

//EGL 不支持多线程，单能在子线程运行

void *drawTh(void *args) {
    eglOpen(eglContexts);
    setWindowBuffersGeometry(eglContexts, 2000, 2000);
    linkWindow(eglContexts);
    EGLint re = eglGetError();
    LOGE("re %d ", re);
    if (re == EGL_SUCCESS) {
        LOGE("re EGL_SUCCESS ");
    }

    init(eglContexts->width, eglContexts->height);

    GLenum glre = glGetError();
    LOGE("gl re %d ", glre);

    draw(eglContexts->width, eglContexts->height);
    GLenum glre2 = glGetError();
    LOGE("gl re2 %d ", glre2);
    display(eglContexts);
}

JNIEXPORT jstring JNICALL
Java_com_example_testopengles_MainActivity_stringFromJNI(JNIEnv *env, jobject instance) {
    return (*env)->NewStringUTF(env, "333333");
}

JNIEXPORT void JNICALL
Java_com_example_testopengles_MainActivity_display(JNIEnv *env, jobject instance, jobject surface) {

    eglContexts = (EGLContexts *) malloc(sizeof(EGLContexts));
    eglContexts->window = 0;
    eglContexts->eglDisplay = 0;
    eglContexts->eglSurface = 0;
    eglContexts->eglContext = 0;
    eglContexts->eglFormat = 0;//颜色格式
    eglContexts->config = 0;

    getWindow(eglContexts, env, surface);

    pthread_t p_id;
    pthread_create(&p_id, NULL, drawTh, NULL);
}


JNIEXPORT void JNICALL
Java_com_example_testopengles_MainActivity_draw(JNIEnv *env, jobject instance) {


}
