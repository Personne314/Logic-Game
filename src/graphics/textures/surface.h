#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <format>

#include "../../utils/logger.hpp"



/**
 * @class Surface
 * @brief Wrapper arround an SDL_Surface.
 */
class Surface
{
public :

	Surface() : m_surface(nullptr) {}
	Surface(SDL_Surface* surface) : m_surface(surface) {}
	Surface(Surface& surface) = delete;
	Surface(Surface&& s) : m_surface(s.m_surface) { s.m_surface = nullptr; }
	~Surface();

	void free();
	void createSurface(
		uint32_t width, uint32_t height, uint32_t depth = 32,
		uint32_t rmask = 0x000000FF, uint32_t gmask = 0x0000FF00, 
		uint32_t bmask = 0x00FF0000, uint32_t amask = 0xFF000000, 
		uint32_t flags = 0
	);

	void convertSurface(uint32_t format = SDL_PIXELFORMAT_RGBA8888);
	void blitSurface(const Surface& surface, SDL_Rect& src, SDL_Rect& dst);
	void fillRect(const SDL_Rect& rect, const SDL_Color& color);

	void load(const std::string& path);
	void save(const std::string& path) const { IMG_SavePNG(m_surface, path.c_str()); }

	void* getPixels() const { return m_surface->pixels; }
	SDL_Rect getRect() const { return {0,0, m_surface->w, m_surface->h}; }
	uint32_t getWidth() const { return m_surface->w; }
	uint32_t getHeight() const { return m_surface->h; }
	bool getInit() const { return m_surface != nullptr; }

private :

	SDL_Surface* m_surface;	// Pointer to the managed SDL_Surface.

};
