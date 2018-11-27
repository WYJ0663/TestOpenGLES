//
// Created by yijunwu on 2018/11/26.
//
#define GLES_STRINGIZE(x)   #x


//
// Created by yijunwu on 2018/11/26.
//
#define GLES_STRINGIZE(x)   #x

//失败
//static const char VERTEX_SHADER[] = GLES_STRINGIZE(
//        #version 300 es
//        layout(location = 0) in vec4 vPosition;
//        void main(){
//        gl_Position = vPosition;
//        }
//);
//
//static const char FRAGMENT_SHADER[] =GLES_STRINGIZE(
//        #version 300 es
//        precision mediump float;
//        out vec4 fragColor;
//        void main(){
//        fragColor = vec4(1.0,1.0,0.0,1.0);
//        }
//);

static const char VERTEX_SHADER[] =
        "#version 300 es\n"
        "layout(location = 0) in vec4 vPosition;\n"
        "void main(){\n"
        "gl_Position = vPosition;\n"
        "}\n";

//static const char FRAGMENT_SHADER[] =
//        "#version 300 es\n"
//        "precision mediump float;\n"
//        "out vec4 fragColor;\n"
//        "void main(){\n"
//        "fragColor = vec4(1.0,1.0,0.0,1.0);\n"
//        "}\n";

static const char FRAGMENT_SHADER[] =
        "#version 300 es\n"
        "precision mediump float;\n"
        "out vec4 fragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main(){\n"
        "fragColor = ourColor;\n"
        "}\n";


//失败
//static const char VERTEX_SHADER[] =
//        "#version 300 es\n"
//        "layout (location = 0) in vec3 position;\n"
//        "out vec4 vertexColor;\n"
//        "void main(){\n"
//        "gl_Position = vec4(position, 1.0); \n"
//        "vertexColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
//        "}\n";
//
//static const char FRAGMENT_SHADER[] =
//        "#version 300 es\n"
//        "out vec4 fragColor;\n"
//        "void main(){\n"
//        "fragColor = vertexColor;\n"
//        "}\n";

