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
	
	bool up() const { return m_up; }
	bool left() const { return m_left; }
	bool right() const { return m_right; }
	bool down() const { return m_down; }

private:

	bool m_close;	// true if a close event was received.
	
	bool m_up;		// true if the up key is pressed.
	bool m_left;	// true if the left key is pressed.
	bool m_right;	// true if the right key is pressed.
	bool m_down;	// true if the down key is pressed.

};
