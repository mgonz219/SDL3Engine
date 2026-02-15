#include "glad/glad.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"

#include "SDL_Sys.h"
#include "window.h"
#include "GLContext.h"


int main() {
    SDL_Sys sys;

    

    Window window; // MUST create with SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    GLContext context(window);
    context.makeCurrent(window);

    


    glViewport(0, 0, 1920, 1080);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // glad test
    glCreateShader(GL_VERTEX_SHADER);

    bool running = true;
    while (running) {
        glClear(GL_COLOR_BUFFER_BIT);
        context.swap(window);
    }

    return 0;
}
