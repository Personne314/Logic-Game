#include "game.h"



Game::Game(const Events &events, uint32_t width, uint32_t height) :
	m_init(false),
	vao(),
	shader("shader"),
	cam(width, height)
{

	float vertices[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	void* data[]       = { vertices };
	uint32_t sizes[]   = { 2 };
	uint32_t types[]   = { GL_FLOAT };
	uint32_t len       = 6;
	uint32_t n         = 1;

	vao.pushData(data, sizes, types, len, n);


	cam.setHeight(8);

	grid = new Grid(events, width, height);
	grid->setBackgroundColor(Color(0.1, 0.1, 0.12, 1.0));
	grid->setMajorColor(Color(0.2, 0.4, 0.4, 1.0));
	grid->setMinorColor(Color(0.2, 0.25, 0.3, 1.0));

	grid->getCamera().setHeight(8);


	m_init = true;
}

Game::~Game()
{
	delete grid;
}



void Game::render(double elapsed_time)
{

	grid->update(elapsed_time);
	grid->render();

	shader.use();
	vao.bind();
		glUniformMatrix4fv(shader.getUniformLocation("viewport"), 1, GL_FALSE, glm::value_ptr(cam.getViewport()));
		glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.unbind();
	
}
