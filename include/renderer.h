#pragma once

//forward declare
struct SDL_Renderer;
struct SDL_Rect;
struct Window;

class Renderer {
	public:

		SDL_Renderer* renderer = nullptr;
		Renderer(Window& window);
		~Renderer();


		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete; 

		SDL_Renderer* get() const { return renderer; }
		
		Renderer(Renderer&& other) noexcept; 


		Renderer& operator=(Renderer&& other) noexcept;

		


		void clearScreen();

		void drawFullRect();

		
		


	private:

		


};
