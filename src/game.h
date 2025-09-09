#pragma once

#include <stdint.h>

#include "graphics/objects/vao.h"
#include "graphics/objects/shader.h"
#include "graphics/camera.h"
#include "interface/grid.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Game
{
public:

	Game(const Events &events, uint32_t width, uint32_t height);
	~Game();

	void render(double elapsed_time);

	bool isInit() const { return m_init; };

private:

	bool m_init;


	VAO vao;
	Shader shader;
	Camera cam;

	Grid* grid;

};
