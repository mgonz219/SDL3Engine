#pragma once
struct SDL_Surface;

class Surface {


public:

	SDL_Surface* surf;
	Surface();
	~Surface();


	Surface(const Surface&) = delete;
	Surface& operator=(const Surface&) = delete; // THESE TWO LINES DISABLE COPYING for memory reasons

	// but we still want to transfer ownership when returning by value and storing it in containers 
	// move constructor
	Surface(Surface&& other) noexcept; // double ampersand means "i am constructing from an object whose resources I am allowed to take"
	// in other words above transfer ownership INSTEAD of copying

	// move assignemnt: used when both objects exist
	Surface& operator=(Surface&& other) noexcept;

	








private:
};