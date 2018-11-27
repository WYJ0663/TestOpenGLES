//
// Created by yijunwu on 2018/11/22.
//
#include <GLES2/gl2.h>
#include <malloc.h>
#include "gles_tr.h"
#include "../main/log.h"
#include "shader.h"
#include "../main/gles.h"
#include "../main/matrix.h"

static const GLfloat VERTEX[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
};

static const GLfloat VERTEX4[] = {
        -1.0f, 1.0f,    //左上角
        -1.0f, -1.0f,   //左下角
        1.0f, 1.0f,     //右上角
        1.0f, -1.0f     //右下角
};


GLuint program;

GLboolean init(int width, int height) {
    LOGE("VERTEX_SHADER %s FRAGMENT_SHADER %s", VERTEX_SHADER, FRAGMENT_SHADER)
    program = createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!program) {
        LOGE("Program fail");
        return GL_FALSE;
    }

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    return GL_TRUE;
}


void draw(int width, int height) {
    LOGE("w h %d %d ", width, height);
    //使用
    glClearColor(0, 0, 0, 1);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    //矩阵
    float *matrix = IJK_GLES2_loadOrtho(NULL, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
//    float *matrix = getRotateM(NULL, 0, 270, 0, 0, 1);
//    float *matrix = setLookAtM(NULL, 0, 0, 0, -3, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    GLint maMVPMatrixHandle = glGetUniformLocation(program, "uMVPMatrix");
    glUniformMatrix4fv(maMVPMatrixHandle, 1, GL_FALSE, matrix);

    GLint vertexColorLocation = glGetUniformLocation(program, "ourColor");
    glUniform4f(vertexColorLocation, 1.0f, 0.0f, 1.0f, 1.0f);

    //3角形
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, VERTEX);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

    //4边形
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, VERTEX4);
//    glEnableVertexAttribArray(0);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
