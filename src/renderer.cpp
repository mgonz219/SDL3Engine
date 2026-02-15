#include "renderer.h"
#include "glad/glad.h"
#include "SDL3/SDL.h"

void Renderer::setViewport(int w, int h){
	glViewport(0, 0, w, h); /* viewport = region of window openGL can draw onto
							*/
}

void Renderer::setClearColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

void Renderer::clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}