//
// Created by yijunwu on 2018/11/26.
//
#define GLES_STRINGIZE(x)   #x

//
//static const char VERTEX_SHADER[] =
//        "attribute vec4 vPosition;\n"
//        "attribute vec2 vCoordinate;\n"
//        "uniform mat4 vMatrix;\n"
//        "varying vec2 aCoordinate;\n"
//        "void main(){\n"
//        "    gl_Position=vMatrix*vPosition;\n"
//        "    aCoordinate=vCoordinate;\n"
//        "}\n";
//
//static const char FRAGMENT_SHADER[] =
////        "#version 300 es\n"
//        "precision mediump float;\n"
//        "uniform sampler2D vTexture;\n"
//        "varying vec2 aCoordinate;\n"
//        "void main(){\n"
//        "    gl_FragColor=texture2D(vTexture,aCoordinate);\n"
//        "}\n";


//static const char VERTEX_SHADER[] =
//        "#version 300 es\n"
//        "layout(location = 0) in vec4 vPosition;\n"
//        "void main(){\n"
//        "gl_Position = vPosition;\n"
//        "}\n";
//
//
//static const char FRAGMENT_SHADER[] =
//        "#version 300 es\n"
//        "precision mediump float;\n"
//        "out vec4 fragColor;\n"
//        "uniform vec4 ourColor;\n"
//        "void main(){\n"
//        "fragColor = ourColor;\n"
//        "}\n";