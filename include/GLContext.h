#pragma once
#include <SDL3/SDL.h>


class Window;

class GLContext{

public:

    GLContext() = default;
    explicit GLContext(Window& window);
    ~GLContext();

    GLContext(const GLContext&) = delete;
    GLContext& operator=(const GLContext&) = delete;

    GLContext(GLContext&& other) noexcept;
    GLContext& operator=(GLContext&& other) noexcept;

    static void makeCurrent(Window& window);
    void swap(Window& window);

    static void setDefaultAttributes(); // static: can be called without an existing GL object.
    void setViewport(int w, int h);
    SDL_GLContext ctx = nullptr;



private: 
    
};