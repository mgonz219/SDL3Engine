/*

#include "shader.h"
#include "glad/glad.h"
#include "SDL3/SDL.h"




Shader(const string& vertexSrc, const string& fragmentSrc){
        std::string vertexCode = readFile(vertexPath);
        std::string fragmentCode = readFile(fragmentPath);

        GLUint vertexShader = compileStage(GL_VERTEX_SHADER, vertexCode);
        GLuint fragmentShader = compileStage(GL_FRAGMENT_SHADER, fragmentCode);

        programID = linkProgram(vertexShader, fragmentShadeR);;


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
}

//
static GLuint compileShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetShaderInfoLog(s, len, nullptr, log.data());
        std::fprintf(stderr, "Shader compile error:\n%s\n", log.c_str());
        glDeleteShader(s);
        return 0;
    }
    return s;
    
}


*/
