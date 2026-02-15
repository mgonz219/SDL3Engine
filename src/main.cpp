#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"

#include "renderer.h"
//#include "SDL_Sys.h"
#include "window.h"
#include "GLContext.h"

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

static GLuint makeProgram(const char* vsSrc, const char* fsSrc) {
    GLuint vs = compileShader(GL_VERTEX_SHADER, vsSrc);
    if (!vs) return 0;
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSrc);
    if (!fs) { glDeleteShader(vs); return 0; }

    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLint ok = 0;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetProgramInfoLog(p, len, nullptr, log.data());
        std::fprintf(stderr, "Program link error:\n%s\n", log.c_str());
        glDeleteProgram(p);
        return 0;
    }
    return p;
}



int main() {
    SDL_ClearError();
    if (SDL_Init(SDL_INIT_VIDEO) == 0) { // replace with SDL_Sys
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    int width = 1280, height = 720;

    SDL_Window* win = SDL_CreateWindow(
        "Cube Demo (SDL3 + OpenGL)",
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (!win) {
        std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(win);
    if (!ctx) {
        std::fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_GL_MakeCurrent(win, ctx);
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::fprintf(stderr, "Failed to init GLAD\n");
        SDL_GL_DestroyContext(ctx);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    std::printf("OpenGL: %s\n", glGetString(GL_VERSION));
    glEnable(GL_DEPTH_TEST);

    const char* vsSrc = R"GLSL(
        #version 330 core
        layout (location=0) in vec3 aPos;
        layout (location=1) in vec3 aColor;

        out vec3 vColor;

        uniform mat4 uModel;
        uniform mat4 uView;
        uniform mat4 uProj;

        void main() {
            vColor = aColor;
            gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
        }
    )GLSL";

    const char* fsSrc = R"GLSL(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(vColor, 1.0);
        }
    )GLSL";

    GLuint prog = makeProgram(vsSrc, fsSrc);
    if (!prog) {
        SDL_GL_DestroyContext(ctx);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    GLint uModel = glGetUniformLocation(prog, "uModel");
    GLint uView  = glGetUniformLocation(prog, "uView");
    GLint uProj  = glGetUniformLocation(prog, "uProj");

    float vertices[] = {
        // pos                  // color
        -0.5f,-0.5f,-0.5f,      1.0f,0.0f,0.0f,  // 0
         0.5f,-0.5f,-0.5f,      0.0f,1.0f,0.0f,  // 1
         0.5f, 0.5f,-0.5f,      0.0f,0.0f,1.0f,  // 2
        -0.5f, 0.5f,-0.5f,      1.0f,1.0f,0.0f,  // 3
        -0.5f,-0.5f, 0.5f,      1.0f,0.0f,1.0f,  // 4
         0.5f,-0.5f, 0.5f,      0.0f,1.0f,1.0f,  // 5
         0.5f, 0.5f, 0.5f,      1.0f,1.0f,1.0f,  // 6
        -0.5f, 0.5f, 0.5f,      0.2f,0.2f,0.2f   // 7
    };

    unsigned int indices[] = {
        0,1,2, 2,3,0,   // back
        4,5,6, 6,7,4,   // front
        4,7,3, 3,0,4,   // left
        1,5,6, 6,2,1,   // right
        4,5,1, 1,0,4,   // bottom
        3,2,6, 6,7,3    // top
    };

    GLuint vao=0, vbo=0, ebo=0;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    bool running = true;
    bool paused = false;
    Uint64 prevTicks = SDL_GetTicks();

    // ensure initial viewport
    glViewport(0, 0, width, height);

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;

            if (e.type == SDL_EVENT_KEY_DOWN) {
                if (e.key.key == SDLK_ESCAPE) running = false;
                if (e.key.key == SDLK_SPACE) paused = !paused;
            }

            if (e.type == SDL_EVENT_WINDOW_RESIZED) {
                width = e.window.data1;
                height = e.window.data2;
                glViewport(0, 0, width, height);
            }
        }

        Uint64 nowTicks = SDL_GetTicks();
        float t = (float)nowTicks / 1000.0f;
        (void)prevTicks; prevTicks = nowTicks;

        glm::mat4 model(1.0f);
        if (!paused) {
            model = glm::rotate(model, t, glm::vec3(0.3f, 1.0f, 0.2f));
        }

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        float aspect = (height == 0) ? 1.0f : (float)width / (float)height;
        glm::mat4 proj = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);

        glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(prog);
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uView,  1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uProj,  1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

        SDL_GL_SwapWindow(win);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(prog);

    SDL_GL_DestroyContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}