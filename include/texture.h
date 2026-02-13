#pragma once

struct SDL_Texture;

class Texture {
	public:

		Texture();
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;



		Texture(Texture&& other) noexcept;


		Texture& operator=(Texture&& other) noexcept;

		Texture& operator=(Texture&&) noexcept;


	private:


};