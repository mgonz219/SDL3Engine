#include "glad/glad.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"

#include "SDL_Sys.h"
#include "window.h"


int main() {
    SDL_Sys sys;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    Window window; // MUST create with SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE

    SDL_GLContext ctx = SDL_GL_CreateContext(window.get());
    if (!ctx) {
        SDL_Log("SDL_GL_CreateContext failed: %s", SDL_GetError());
        return 1;
    }

    // MUST be current BEFORE gladLoadGLLoader
    if (!SDL_GL_MakeCurrent(window.get(), ctx)) {
        SDL_Log("SDL_GL_MakeCurrent failed: %s", SDL_GetError());
        return 1;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_Log("gladLoadGLLoader failed");
        return 1;
    }

    glViewport(0, 0, 1920, 1080);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // glad test
    glCreateShader(GL_VERTEX_SHADER);

    bool running = true;
    while (running) {
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window.get());
    }

    return 0;
}
