#pragma once

#include <SDL2/SDL.h>



/**
 * @class Events
 * @brief Manage all keyboard/mouse events.
 */
class Events 
{
public:

	Events();
	~Events() = default;

	void poll();

	bool close() const { return m_close; }

private:

	bool m_close;	// true if a close event was received.

};
