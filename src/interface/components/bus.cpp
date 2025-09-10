#include "bus.h"



Bus::Bus(const Shader &shader, const Camera &camera) :
	m_shader(shader),
	m_camera(camera),
	m_vao(),
	m_size(4),
	m_state(0b1101)
{

	float vertices[] = {
		-0.5f, -0.5f, -1, -1,
		 0.5f, -0.5f,  1, -1,
		 0.5f,  0.5f,  1,  1,

		-0.5f, -0.5f, -1, -1,
		 0.5f,  0.5f,  1,  1,
		-0.5f,  0.5f, -1,  1
	};

	uint8_t type = Direction::DOWN + Direction::RIGHT + Direction::UP + (Direction::RIGHT << 4);
	uint8_t vertices_types[] = {
		type, type, type, type, type, type
	};

	void* data[]       = { vertices, vertices_types };
	uint32_t sizes[]   = { 4, 1 };
	uint32_t types[]   = { GL_FLOAT, GL_UNSIGNED_BYTE };
	uint32_t len       = 6;
	uint32_t n         = 2;

	m_vao.pushData(data, sizes, types, len, n);

}

Bus::~Bus()
{

}



void Bus::render()
{
	m_shader.use();
	m_vao.bind();
		glUniform1ui(m_shader.uniform("size"), m_size);
		glUniform1ui(m_shader.uniform("state"), m_state);
		glUniform4f(m_shader.uniform("off_color"), 1,0,0,1);
		glUniform4f(m_shader.uniform("on_color"), 0,1,0,1);
		glUniformMatrix4fv(
			m_shader.uniform("viewport"), 1, GL_FALSE, 
			glm::value_ptr(m_camera.getViewport())
		);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	m_vao.unbind();
}



void Bus::setState(uint32_t id)
{
	if (id >= m_size) return;
	m_state |= (1 << id);
}

void Bus::resetState(uint32_t id)
{
	if (id >= m_size) return;
	m_state &= ~(1 << id);
}



bool Bus::getState(uint32_t id)
{
	if (id >= m_size) return false;
	return m_state & (1 << id);
}
