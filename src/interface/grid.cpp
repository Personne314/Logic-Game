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
		glUniform4f(
			m_shader.uniform("background_color"), 
			m_color_background.r, m_color_background.g, m_color_background.b, m_color_background.a
		);
		glUniform4f(
			m_shader.uniform("major_color"),
			m_color_major.r, m_color_major.g, m_color_major.b, m_color_major.a
		);
		glUniform4f(
			m_shader.uniform("minor_color"),
			m_color_minor.r, m_color_minor.g, m_color_minor.b, m_color_minor.a
		);
		glUniformMatrix4fv(
			m_shader.uniform("inv_viewport"), 
			1, GL_FALSE, glm::value_ptr(m_camera.getInvViewport())
		);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	m_vao.unbind();
}
