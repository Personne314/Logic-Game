#include "grid.h"




Grid::Grid(const Camera &camera, const Shader &shader) :
	m_camera(camera),	
	m_shader(shader),
	m_vao()
{

	float vertices[] = {-1,-1, 1,1, -1,1, -1,-1, 1,-1, 1,1};
	void* data[]       = {vertices};
	uint32_t sizes[]   = {2};
	uint32_t types[]   = {GL_FLOAT};
	uint32_t len       = 6;
	uint32_t n         = 1;
	m_vao.pushData(data, sizes, types, len, n);

}

Grid::~Grid()
{

}

void Grid::render()
{
	m_shader.use();
	m_vao.bind();
		glUniformMatrix4fv(
			m_shader.getUniformLocation("inv_viewport"), 
			1, GL_FALSE, glm::value_ptr(m_camera.getInvViewport())
		);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	m_vao.unbind();
}
