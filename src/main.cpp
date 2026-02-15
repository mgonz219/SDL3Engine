#include "glad/glad.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"
#include "renderer.h"
#include "SDL_Sys.h"
#include "window.h"
#include "GLContext.h"


int main() {
    SDL_Sys sys;

    

    Window window;
    GLContext context(window);
    context.makeCurrent(window);

    
    Renderer renderer;
    renderer.setViewport(1920,1080);
    renderer.setClearColor(0.2f,0.3f,0.3f,1.0f);
    

    // glad test
    glCreateShader(GL_VERTEX_SHADER);

    bool running = true;
    while (running) {
        renderer.clear();
        context.swap(window);
    }

    return 0;
}
