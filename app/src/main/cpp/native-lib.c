#include <jni.h>

JNIEXPORT jstring JNICALL
Java_com_example_testopengles_MainActivity_stringFromJNI(JNIEnv *env, jobject instance) {
    return (*env)->NewStringUTF(env, "333333");
}

JNIEXPORT void JNICALL
Java_com_example_testopengles_MainActivity_display(JNIEnv *env, jobject instance, jobject surface) {

    // TODO

}