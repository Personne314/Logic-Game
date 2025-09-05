#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <memory>
#include <string>
#include <stdint.h>

#include "utils/events.h"
#include "utils/logger.h"



/**
 * @class Window
 * @brief Setup the window and launch the game.
 */
class Window
{
public:

	Window(int w, int h, const std::string& name);
	~Window();

	void start();

private:

	bool initGL();
	void loop();

	bool m_init;	// true if the windows was well initialized.

	SDL_GLContext m_context;	// OpenGL context for rendering.
	SDL_Window* m_window;		// The SDL window to use.
	int m_width;	// Window width.
	int m_height;	// Window height.

};
