#pragma once


struct SDL_Window;

class Window {
	public:
		SDL_Window* window = nullptr;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		SDL_Window* get() const { return window; }

	

		Window(Window&& other) noexcept;


		Window& operator=(Window&& other) noexcept;

		

		Window();
		~Window();
		

	private:

		


};
