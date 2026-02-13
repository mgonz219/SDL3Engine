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

GLContext:GLContext(Window& winodw){
    ctx = SDL_GL_CreateContext(window.get());
    if(!ctx){
        throw std::runtime_error(std::string("SDL_GL_CreateContext failed: ") + SDL_GetError());
    }

    makeCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        throw std::runtime_error("gladLoadGLLoader failed");
    }
}

void GLContext::makeCurrent(Window& window) {
    if(!SDL_GL_MakeCurrent(window.get(),ctx)){
        throw std::runtime_error(std::string("SDL_GL_MakeCurrent failed: ") + SDL_GetError());
    }   
}