#pragma once

#include <stdint.h>



class Game
{
public:

	Game(uint32_t width, uint32_t height);
	~Game();

	void render(double elapsed_time);

	bool isInit() const { return m_init; };

private:

	bool m_init;

};
