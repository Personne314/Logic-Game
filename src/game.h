#pragma once

#include <stdint.h>

#include "graphics/objects/shader.h"
#include "interface/grid.h"
#include "interface/components/bus.h"
#include "math/color.hpp"



class Game
{
public:

	Game(const Events &events, uint32_t width, uint32_t height);
	~Game();

	void render(double elapsed_time);

	bool isInit() const { return m_init; };

private:

	bool m_init;

	Shader shader;

	Grid* grid;
	BusFactory *bus;

	std::unique_ptr<Bus> test_bus;
	
};
