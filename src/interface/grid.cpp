#include "grid.h"




Grid::Grid(const Events &events, uint32_t width, uint32_t height) :
	m_camera(width, height),	
	m_shader("grid"),
	m_vao(),
	m_events(events)
{

	float vertices[] = {-1,-1, 1,1, -1,1, -1,-1, 1,-1, 1,1};
	void* data[]     = {vertices};
	uint32_t sizes[] = {2};
	uint32_t types[] = {GL_FLOAT};
	uint32_t len     = 6;
	uint32_t n       = 1;
	m_vao.pushData(data, sizes, types, len, n);

}

Grid::~Grid()
{

}



void Grid::update(double elapsed_time)
{

	if (m_events.up()) m_camera.move(0, elapsed_time);
	if (m_events.left()) m_camera.move(-elapsed_time, 0);
	if (m_events.right()) m_camera.move(elapsed_time, 0);
	if (m_events.down()) m_camera.move(0, -elapsed_time);

}

void Grid::render()
{
	m_shader.use();
	m_vao.bind();
		glUniform4f(m_shader.getUniformLocation("background_color"), 0.1, 0.1, 0.12, 1.0);
		glUniform4f(m_shader.getUniformLocation("major_color"), 0.2, 0.4, 0.4, 1.0);
		glUniform4f(m_shader.getUniformLocation("minor_color"), 0.2, 0.25, 0.3, 1.0);
		glUniformMatrix4fv(
			m_shader.getUniformLocation("inv_viewport"), 
			1, GL_FALSE, glm::value_ptr(m_camera.getInvViewport())
		);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	m_vao.unbind();
}
