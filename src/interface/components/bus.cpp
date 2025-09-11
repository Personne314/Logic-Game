#include "bus.h"



Bus::Bus(
	const Shader &shader, 
	const Camera &camera, 
	const std::vector<std::pair<int32_t, int32_t>> &nodes, 
	uint32_t size
) :
	m_shader(shader),
	m_camera(camera),
	m_vao(),
	m_size(size),
	m_state(0)
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
		glUniform4f(m_shader.uniform("off_color"), 0,0.15,0,1);
		glUniform4f(m_shader.uniform("on_color"), 0,0.8,0,1);
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





BusFactory::BusFactory(const Shader &shader, const Camera &camera, const Events &events) :
	m_shader(shader),
	m_camera(camera),
	m_events(events),
	m_nodes(),
	m_preview(),
	m_preview_vao(),
	m_x(0),
	m_y(0)
{

	float vertices[] = {
		-0.5f, -0.5f, -1, -1,
		 0.5f, -0.5f,  1, -1,
		 0.5f,  0.5f,  1,  1,

		-0.5f, -0.5f, -1, -1,
		 0.5f,  0.5f,  1,  1,
		-0.5f,  0.5f, -1,  1
	};

	uint8_t vertices_types[] = {
		0,0,0,0,0,0
	};

	void* data[]       = { vertices, vertices_types };
	uint32_t sizes[]   = { 4, 1 };
	uint32_t types[]   = { GL_FLOAT, GL_UNSIGNED_BYTE };
	uint32_t len       = 6;
	uint32_t n         = 2;

	m_preview_vao.pushData(data, sizes, types, len, n);

}

BusFactory::~BusFactory()
{

}



void BusFactory::update()
{

	// Get the int coordinate of the cursor.
	float x,y;
	m_camera.getCursorPosition(x,y);
	uint32_t i_x = static_cast<int32_t>(std::round(x));
	uint32_t i_y = static_cast<int32_t>(std::round(y));

	if (m_x != i_x || m_y != i_y) update_preview();
	m_x = i_x;
	m_y = i_y;

	// If there are already nodes, force alignment with it.
	if (m_nodes.size()) {
		uint32_t n_x = m_nodes.back().first;
		uint32_t n_y = m_nodes.back().second;
		float dx2 = (n_x-m_x)*(n_x-m_x);
		float dy2 = (n_y-m_y)*(n_y-m_y);
		if (dx2 > dy2) m_y = m_nodes.back().second;
		else m_x = m_nodes.back().first;
	}



	if (m_events.left_click()) add_node();
	if (m_events.right_click()) remove_node();

}



void BusFactory::clear()
{

}



std::unique_ptr<Bus> BusFactory::make() const
{

}



void BusFactory::render() const
{



	// Render the preview 'cursor'.
	m_shader.use();
	m_preview_vao.bind();
		glUniform2f(m_shader.uniform("offset"), m_x, m_y);
		glUniform4f(m_shader.uniform("inner_color"), 0.10,0.15,0.10,1);
		glUniform4f(m_shader.uniform("outer_color"), 0.15,0.3,0.2,1);
		glUniformMatrix4fv(
			m_shader.uniform("viewport"), 1, GL_FALSE, 
			glm::value_ptr(m_camera.getViewport())
		);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	m_preview_vao.unbind();

}



void BusFactory::add_node()
{
	if (m_nodes.size() && m_nodes.back().first == m_x && m_nodes.back().second == m_y) return;
	m_nodes.push_back(std::make_pair(m_x, m_y));
}

void BusFactory::remove_node()
{
	if (m_nodes.size()) m_nodes.pop_back();
}

void BusFactory::update_preview()
{

}
