#include "game.h"



Game::Game(uint32_t width, uint32_t height) :
	m_init(false),
	vao(),
	shader("shader")
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

	m_init = true;
}

Game::~Game()
{

}



void Game::render(double elapsed_time)
{
	shader.use();
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.unbind();
}
