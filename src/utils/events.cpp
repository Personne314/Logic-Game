#include "events.h"



/**
 * @brief Construct an Events.
 */
Events::Events() :
	m_close(false),
	m_up(false),
	m_left(false),
	m_right(false),
	m_down(false),
	m_left_click(false),
	m_right_click(false),
	m_left_click_hold(false),
	m_right_click_hold(false)
{

}



/**
 * @brief Process all received events since the last call.
 */
void Events::poll() {


	// Reset temp events.
	m_left_click = false;
	m_right_click = false;

	// Loop over each event.
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		// Quit event : alt+f4 or close button.
		case SDL_QUIT:	m_close = true;	break;

		// Detect a pressure on a key.
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_UP:		m_up = true;	break;
			case SDLK_LEFT:		m_left = true;	break;
			case SDLK_RIGHT:	m_right = true;	break;
			case SDLK_DOWN:		m_down = true;	break;
			}
			break;

		// Detect a pressure release on a key.
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_UP:		m_up = false;		break;
			case SDLK_LEFT:		m_left = false;		break;
			case SDLK_RIGHT:	m_right = false;	break;
			case SDLK_DOWN:		m_down = false;		break;
			}
			break;

		// Detect a pressure on a mouse button
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:	
				m_left_click = true;	
				m_left_click_hold = true;	break;
			case SDL_BUTTON_RIGHT:	
				m_right_click = true;
				m_right_click_hold = true;	break;
			}
			break;

		// Detect a release of pressure on a mouse button
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:	m_left_click_hold = false;	break;
			case SDL_BUTTON_RIGHT:	m_right_click_hold = false;	break;
			}
			break;

		}
		
	} 

}
