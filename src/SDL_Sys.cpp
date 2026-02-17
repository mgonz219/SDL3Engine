#include "SDL_Sys.h"
#include "SDL3/SDL.h"
#include <iostream>

#include <stdexcept>


SDL_Sys::SDL_Sys() {
    if(SDL_Init(SDL_INIT_VIDEO) == 0) { 
        std::string err = SDL_GetError();
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        throw std::runtime_error(err);
    }

    
}


SDL_Sys::~SDL_Sys() {
    SDL_Quit();
}







