//
// Created by yijunwu on 2018/11/22.
//

#ifndef TESTOPENGLES_GLES_H
#define TESTOPENGLES_GLES_H

#include <GLES2/gl2.h>


GLuint createShader(GLenum shaderType, const char *src);

GLuint createProgram(const char *vtxSrc, const char *fragSrc);

#endif //TESTOPENGLES_GLES_H
