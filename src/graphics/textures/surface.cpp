#include "surface.h"



/**
 * @brief Delete the Surface.
 */
Surface::~Surface() 
{
	free();
}



/**
 * @brief Free the contained surface.
 */
void Surface::free()
{
	if (!m_surface) return;
	SDL_FreeSurface(m_surface);
	m_surface = nullptr;
}

/**
 * @brief Create a surface with given properties
 * @param width The surface width.
 * @param height The surface height.
 * @param depth The surface depth (in bits).
 * @param rmask The pixels red component mask.
 * @param gmask The pixels green component mask.
 * @param bmask The pixels blue component mask.
 * @param amask The pixels alpha component mask.
 * @param flags Surface flags. Should be set to 0.
 */
void Surface::createSurface(
	uint32_t width, uint32_t height, uint32_t depth, 
	uint32_t rmask, uint32_t gmask, uint32_t bmask, uint32_t amask, 
	uint32_t flags
) {
	free();

	// Create the surface.
	m_surface = SDL_CreateRGBSurface(
		flags, width, height, depth, 
		rmask, gmask, bmask, amask
	);

	// Ensure its created.
	if (!m_surface) {
		print_error(
			"Failed to create a surface (width:{}, height:{}, depth:{}, "
			"rmask:{}, gmask:{}, bmask:{}, amask:{}, flags:{}) : {}",
			width, height, depth, rmask, gmask, bmask, amask, flags, IMG_GetError()
		);
	}
}



/**
 * @brief Convert a surface to a given format.
 * @param format The format to use.
 */
void Surface::convertSurface(uint32_t format)
{
	SDL_Surface* temp = SDL_ConvertSurface(m_surface, m_surface->format, format);
	if (!temp) {
		print_error("Failed to convert surface : {}", SDL_GetError());
		return;
	} 
	delete m_surface;
	m_surface = temp;
}

/**
 * @brief Blit a surface to this one.
 * @param surface The surface to blit.
 * @param src The rect of surface to blit.
 * @param dst The rect where to blit the surface.
 */
void Surface::blitSurface(const Surface& surface, SDL_Rect& src, SDL_Rect& dst)
{
	if (!m_surface) return;
	if (SDL_BlitSurface(surface.m_surface, &src, m_surface, &dst)) {
		print_error("Failed to blit surface : {}", SDL_GetError());
	}
}

/**
 * @brief Fill a rect of the surface with a color.
 * @param rect The rect to fill.
 * @param color The color to use.
 */
void Surface::fillRect(const SDL_Rect& rect, const SDL_Color& color)
{
	SDL_FillRect(
		m_surface, &rect, 
		SDL_MapRGBA(m_surface->format,color.r, color.g, color.b, color.a)
	);
}



/**
 * @brief Load a surface from a file.
 * @param path The path of the file to load.
 */
void Surface::load(const std::string& path)
{
	free();
	m_surface = IMG_Load(path.c_str());
	if (!m_surface) {
		print_error("Failed to load surface from file '{}' : {}", path, IMG_GetError());
	}
}
