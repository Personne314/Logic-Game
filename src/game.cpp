#include "game.h"



Game::Game(const Events &events, uint32_t width, uint32_t height) :
	m_init(false),
	shader("bus")
{


	grid = new Grid(events, width, height);
	grid->setBackgroundColor(Color(0.1, 0.1, 0.12, 1.0));
	grid->setMajorColor(Color(0.2, 0.4, 0.4, 1.0));
	grid->setMinorColor(Color(0.2, 0.25, 0.3, 1.0));

	grid->getCamera().setHeight(8);

	bus = new BusFactory(shader, grid->getCamera(), events);
	bus->setBusWidth(0.5);

	m_init = true;
}

Game::~Game()
{
	delete bus;
	delete grid;
}



void Game::render(double elapsed_time)
{

	static bool t = false;

	grid->update(elapsed_time);
	grid->render();

	bus->update();
	bus->render();

	if (!t && bus->done()) {
		t = true;
		test_bus = bus->make();
	}

	if (test_bus) test_bus->render();


}
