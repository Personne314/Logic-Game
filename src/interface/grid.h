#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../graphics/camera.h"
#include "../graphics/objects/shader.h"
#include "../graphics/objects/vao.h"



class Grid
{
public:

	Grid(const Camera &camera, const Shader &shader);
	~Grid();

	void render();

private:

	const Camera &m_camera;
	const Shader &m_shader;
	VAO m_vao;

};
