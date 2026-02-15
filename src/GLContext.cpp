#include "GLContext.h"
#include "window.h"
#include <stdexcept>
#include <utility>
#include <glad/glad.h>




void GLContext::setDefaultAttributes() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Optional but common:
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

GLContext::GLContext(Window& window){
    ctx = SDL_GL_CreateContext(window.get());
    if(!ctx){
        throw std::runtime_error(std::string("SDL_GL_CreateContext failed: ") + SDL_GetError());
    }

    GLContext::makeCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        throw std::runtime_error("gladLoadGLLoader failed");
    }
}



void GLContext::makeCurrent(Window& window) {
    if (SDL_GL_MakeCurrent(window.get(), ctx) != 0) {   // NOTE: SDL returns 0 on success, not bool
        throw std::runtime_error(std::string("SDL_GL_MakeCurrent failed: ") + SDL_GetError());
    }
}

void GLContext::swap(Window& window){
    SDL_GL_SwapWindow(window.get());
}

void GLContext::setViewport(int w, int h){
    glViewport(0,0,w,h);
}

GLContext::~GLContext(){
    if(ctx) SDL_GL_DestroyContext(ctx);
}

GLContext::GLContext(GLContext&& other) noexcept : ctx(other.ctx){
    other.ctx = nullptr;
}

GLContext& GLContext::operator=(GLContext&& other) noexcept{
    if(this != &other){
        if(ctx) SDL_GL_DestroyContext(ctx);
        ctx = other.ctx;
        other.ctx = nullptr;
    }
    return *this;
}