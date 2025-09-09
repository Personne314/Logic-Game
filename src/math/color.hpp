#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>



/**
 * @brief Small class representing a RGBA color.
 */
class Color
{
public:

	Color() : r(0), g(0), b(0), a(0) {}
	Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	Color(SDL_Color color) : r(color.r/255.f), g(color.g/255.f), b(color.b/255.f), a(color.a/255.f) {}

	~Color() = default;

	SDL_Color toSDL() const { return {
		static_cast<uint8_t>(r*255),
		static_cast<uint8_t>(g*255),
		static_cast<uint8_t>(b*255),
		static_cast<uint8_t>(a*255)};
	}

	float r;	// Red component of the color.
	float g;	// Green component of the color.
	float b;	// Blue component of the color.
	float a;	// Alpha component of the color.

};

