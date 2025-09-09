#pragma once 

#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>

#include "../graphics/camera.h"
#include "../graphics/objects/shader.h"
#include "../graphics/objects/vao.h"
#include "../utils/events.h"



class Grid
{
public:

	Grid(const Events &events, uint32_t width, uint32_t height);
	~Grid();

	void update(double elapsed_time);
	void render();

	void setBackgroundColor(SDL_Color color) { m_color_background = color; }
	void setMajorColor(SDL_Color color) { m_color_major = color; }
	void setMinorColor(SDL_Color color) { m_color_minor = color; }

	Camera &getCamera() { return m_camera; }

private:

	Camera m_camera;
	Shader m_shader;
	VAO m_vao;

	SDL_Color m_color_background;
	SDL_Color m_color_major;
	SDL_Color m_color_minor;

	const Events &m_events;

};
