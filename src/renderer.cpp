#include "window.h"
#include <SDL3/SDL.h>
#include "renderer.h"

Renderer::Renderer(Window& window) {
	renderer = SDL_CreateRenderer(window.get(), NULL); // null means let SDL figure out rendering driver
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer);
}

void Renderer::clearScreen() {
	
	SDL_RenderClear(renderer);
	
}



void Renderer::drawFullRect() {
	SDL_FRect rect;              // allocate an actual rect (not a dangling pointer)
	rect.x = 5.0f;
	rect.y = 10.0f;
	rect.w = 1000.0f;
	rect.h = 500.0f;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
	SDL_RenderRect(renderer, &rect);
}



