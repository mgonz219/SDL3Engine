#pragma once
#include <glad/glad.h>

class Renderer {

public:
	void setViewport(int w, int h);
	void setClearColor(float r, float g, float b, float a);
	void clear();

	Renderer() = default;
	~Renderer();



};