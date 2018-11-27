//
// Created by yijunwu on 2018/11/22.
//
#include <GLES2/gl2.h>
#include <malloc.h>
#include <stdbool.h>
#include "gles_tr.h"
#include "../main/log.h"
#include "shader.h"
#include "../main/gles.h"
#include "../main/matrix.h"

#define BYTES_PER_FLOAT 4
#define POSITION_COMPONENT_COUNT 2
#define TEXTURE_COORDINATES_COMPONENT_COUNT 2
#define STRIDE ((POSITION_COMPONENT_COUNT + TEXTURE_COORDINATES_COMPONENT_COUNT)*BYTES_PER_FLOAT)

GLuint glProgram;
GLint positionLoc;
GLuint mTextureID;

GLbyte vShaderStr[] = "attribute vec4 a_Position;  			\n"
                      "attribute vec2 a_TextureCoordinates;   			\n"
                      "varying vec2 v_TextureCoordinates;     			\n"
                      "void main()                            			\n"
                      "{                                      			\n"
                      "    v_TextureCoordinates = a_TextureCoordinates;   \n"
                      "    gl_Position = a_Position;    					\n"
                      "}                                      			\n";

GLbyte fShaderStr[] =
        "precision mediump float; \n"
        "uniform sampler2D u_TextureUnit;                	\n"
        "varying vec2 v_TextureCoordinates;              	\n"
        "void main()                                     	\n"
        "{                                               	\n"
        "    gl_FragColor = vec4(texture2D(u_TextureUnit, v_TextureCoordinates).rgb, 1);  \n"
        "}                                               	\n";


GLboolean init(int width, int height) {
    LOGE("VERTEX_SHADER %s FRAGMENT_SHADER %s", vShaderStr, fShaderStr)
    glProgram = createProgram(vShaderStr, fShaderStr);
    if (!glProgram) {
        LOGE("Program fail");
        return GL_FALSE;
    }
    //纹理
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glEnable(GL_TEXTURE_2D);

    return GL_TRUE;
}

void setUniforms(int uTextureUnitLocation, int textureId) {
    // Pass the matrix into the shader program.
    //glUniformMatrix4fv(uMatrixLocation, 1, false, matrix);

    // Set the active texture unit to texture unit 0.
    glActiveTexture(GL_TEXTURE0);

    // Bind the texture to this unit.
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Tell the texture uniform sampler to use this texture in the shader by
    // telling it to read from texture unit 0.
    glUniform1i(uTextureUnitLocation, 0);
}

const GLfloat sPos[] = {
        -1.0f, 1.0f,    //左上角
        -1.0f, -1.0f,   //左下角
        1.0f, 1.0f,     //右上角
        1.0f, -1.0f     //右下角
};

const GLfloat sCoord[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
};

void draw(int width, int height, char *pixel) {
    // Set the viewport
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0, 1);
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(glProgram);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    glGenerateMipmap(GL_TEXTURE_2D);
    //GL_UNSIGNED_SHORT_5_6_5

    // Retrieve uniform locations for the shader program.
    GLint uTextureUnitLocation = glGetUniformLocation(glProgram, "u_TextureUnit");
    setUniforms(uTextureUnitLocation, mTextureID);

    // Retrieve attribute locations for the shader program.
    GLint aPositionLocation = glGetAttribLocation(glProgram, "a_Position");
    GLint aTextureCoordinatesLocation = glGetAttribLocation(glProgram, "a_TextureCoordinates");

    ////////////////方法一//////////////////
    // Order of coordinates: X, Y, S, T
    // Triangle Fan
//    GLfloat VERTEX_DATA[] = {0.0f, 0.0f, 0.5f, 0.5f,
//                             -1.0f, -1.0f, 0.0f, 1.0f,
//                             1.0f, -1.0f, 1.0f, 1.0f,
//                             1.0f, 1.0f, 1.0f, 0.0f,
//                             -1.0f, 1.0f, 0.0f, 0.0f,
//                             -1.0f, -1.0f, 0.0f, 1.0f};
//
//    glVertexAttribPointer(aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, VERTEX_DATA);
//    glEnableVertexAttribArray(aPositionLocation);
//
//    glVertexAttribPointer(aTextureCoordinatesLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE,
//                          &VERTEX_DATA[POSITION_COMPONENT_COUNT]);
//    glEnableVertexAttribArray(aTextureCoordinatesLocation);
//
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    ////////////////方法二//////////////////
    //传入顶点坐标
    glVertexAttribPointer(aPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, sPos);
    glEnableVertexAttribArray(aPositionLocation);
    //传入纹理坐标
    glVertexAttribPointer(aTextureCoordinatesLocation, 2, GL_FLOAT, GL_FALSE, 0, sCoord);
    glEnableVertexAttribArray(aTextureCoordinatesLocation);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


    glBindTexture(GL_TEXTURE_2D, 0);

}
