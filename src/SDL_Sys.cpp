#include "SDL_Sys.h"
#include "SDL3/SDL.h"
#include <iostream>

#include <stdexcept>


// think of this constructor as an initializer of SDL unerlying stuff, not the class object;
SDL_Sys::SDL_Sys() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::string err = SDL_GetError();
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        throw std::runtime_error(err);
    }
}

SDL_Sys::~SDL_Sys() {
    SDL_Quit();
}








