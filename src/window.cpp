#include "SDL3/SDL.h"
#include "window.h"

Window::Window() {
    constexpr int width = 1920;
    constexpr int height = 1080;

    window = SDL_CreateWindow("title", width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
}

Window::~Window() {
    if (window) SDL_DestroyWindow(window);
}

Window::Window(Window&& other) noexcept : window(other.window) {
    other.window = nullptr;
}

Window& Window::operator=(Window&& other) noexcept {
    if (this != &other) {
        if (window) SDL_DestroyWindow(window);
        window = other.window;
        other.window = nullptr;
    }
    return *this;
}
