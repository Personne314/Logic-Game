#include "events.h"



/**
 * @brief Construct an Events.
 */
Events::Events() :
	m_close(false) 
{

}



/**
 * @brief Process all received events since the last call.
 */
void Events::poll() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:	m_close = true;	break;
		}
	} 

}
