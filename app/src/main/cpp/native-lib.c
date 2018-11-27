#include <jni.h>
#include <malloc.h>
#include <pthread.h>
#include <GLES2/gl2.h>
#include <android/bitmap.h>

#include "main/egl.h"
#include "main/log.h"
#include "texture/gles_tr.h"


EGLContexts *eglContexts;
int width;
int height;
//EGL 不支持多线程，单能在子线程运行

void *drawTh(void *args) {
//    eglOpen(eglContexts);
//    setWindowBuffersGeometry(eglContexts, 2000, 2000);
//    linkWindow(eglContexts);
//    EGLint re = eglGetError();
//    LOGE("re %d ", re);
//    if (re == EGL_SUCCESS) {
//        LOGE("re EGL_SUCCESS ");
//    }
//
//    init(eglContexts->width, eglContexts->height);
//
//    GLenum glre = glGetError();
//    LOGE("gl re %d ", glre);
//
//    draw(eglContexts->width, eglContexts->height);
//    GLenum glre2 = glGetError();
//    LOGE("gl re2 %d ", glre2);
//    display(eglContexts);
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

//    pthread_t p_id;
//    pthread_create(&p_id, NULL, drawTh, NULL);
}
void *drawBitmap(void *args) {

    char *pix = (char *) args;
    LOGE("w h = %d*%d size=%d",width, height, &pix);
    eglOpen(eglContexts);
    setWindowBuffersGeometry(eglContexts, width, height);
    linkWindow(eglContexts);
    EGLint re = eglGetError();
    LOGE("re %d ", re);
    if (re == EGL_SUCCESS) {
        LOGE("re EGL_SUCCESS ");
    }

    init(eglContexts->width, eglContexts->height);

    GLenum glre = glGetError();
    LOGE("gl re %d ", glre);

    draw(eglContexts->width, eglContexts->height, pix);
    GLenum glre2 = glGetError();
    LOGE("gl re2 %d ", glre2);
    display(eglContexts);
}



JNIEXPORT void JNICALL
Java_com_example_testopengles_MainActivity_drawBitmap(JNIEnv *env, jobject instance, jobject bitmap) {
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bitmap, &info) < 0) {
        LOGE("获取bitmat 信息失败");
    }
    width = info.width;
    height = info.height;


    unsigned char *dataFromBmp = NULL;
    AndroidBitmap_lockPixels(env, bitmap, (void **) &dataFromBmp);
    //需要GL_RGBA
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    pthread_t p_id;
    pthread_create(&p_id, NULL, drawBitmap, dataFromBmp);
}

JNIEXPORT void JNICALL
Java_com_example_testopengles_MainActivity_draw(JNIEnv *env, jobject instance, jbyteArray pix_, jint w, jint h) {
    jbyte *pix = (*env)->GetByteArrayElements(env, pix_, NULL);
    width = w;
    height = h;
    pthread_t p_id;
    pthread_create(&p_id, NULL, drawBitmap, pix);

    (*env)->ReleaseByteArrayElements(env, pix_, pix, 0);
}