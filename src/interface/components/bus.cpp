#include "bus.h"





/**
 * @brief Add vertices of a node to the vectors.
 * @param vertices The vector where to store the vertices.
 * @param vertices_types The vector where to store the vertices types.
 * @param width The width of the bus.
 * @param type The type of the node.
 * @param x_offset The offset of the node on the x coordinate.
 * @param y_offset The offset of the node on the y coordinate.
 */
void add_node_vertices(
	std::vector<float> &vertices, 
	std::vector<uint8_t> &vertices_types, 
	const float width, 
	const uint8_t type,
	const int32_t x_offset,
	const int32_t y_offset
) {
	const float half_width = width/2;

	// Node vertices array.
	float array_vertices[] = {
		-half_width+x_offset, -half_width+y_offset, -1, -1,
		 half_width+x_offset, -half_width+y_offset,  1, -1,
		 half_width+x_offset,  half_width+y_offset,  1,  1,
		-half_width+x_offset, -half_width+y_offset, -1, -1,
		 half_width+x_offset,  half_width+y_offset,  1,  1,
		-half_width+x_offset,  half_width+y_offset, -1,  1
	};

	// Node type array.
	uint8_t array_vertices_types[] = {
		type, type, type, type, type, type
	};

	// Append the vertices.
	vertices.insert(
		vertices.end(),
		std::begin(array_vertices),
		std::end(array_vertices)
	);

	// Append the vertices type.
	vertices_types.insert(
		vertices_types.end(),
		std::begin(array_vertices_types),
		std::end(array_vertices_types)
	);

}



void add_bus_vertices(
	std::vector<float> &vertices, 
	std::vector<uint8_t> &vertices_types, 
	const float width, 
	const std::pair<int32_t, int32_t> start,
	const std::pair<int32_t, int32_t> end
	
) {
	const float half_width = width/2;

	const uint8_t inverse = 
		(start.first > end.first || start.second < end.second) * 0b0001'0000;

	const uint8_t type = 
		(start.first == end.first) * (Direction::UP + Direction::DOWN) +
		(start.second == end.second) * (Direction::LEFT + Direction::RIGHT) +
		inverse;

	const bool up = type & Direction::UP;
	const bool left = type & Direction::LEFT;

	const float rect_x1 = 
		std::min(start.first, end.first) +
		left * half_width -
		up * half_width;

	const float rect_y1 = 
		std::min(start.second, end.second) +
		up * half_width -
		left * half_width;

	const float rect_x2 = 
		rect_x1 +
		left * (std::abs((float)(start.first-end.first))-width) +
		up * width;

	const float rect_y2 = 
		rect_y1 +
		up * (std::abs((float)(start.second-end.second))-width) +
		left * width;

	// Node vertices array.
	const float array_vertices[] = {
		rect_x1, rect_y1, -1, -1,
		rect_x2, rect_y1,  1, -1,
		rect_x2, rect_y2,  1,  1,
		rect_x1, rect_y1, -1, -1,
		rect_x2, rect_y2,  1,  1,
		rect_x1, rect_y2, -1,  1
	};

	// Node type array.
	const uint8_t array_vertices_types[] = {
		type, type, type, type, type, type
	};

	// Append the vertices.
	vertices.insert(
		vertices.end(),
		std::begin(array_vertices),
		std::end(array_vertices)
	);

	// Append the vertices type.
	vertices_types.insert(
		vertices_types.end(),
		std::begin(array_vertices_types),
		std::end(array_vertices_types)
	);

}




Bus::Bus(
	const Shader &shader, 
	const Camera &camera, 
	const std::vector<std::pair<int32_t, int32_t>> &nodes, 
	uint32_t size,
	float width
) :
	m_shader(shader),
	m_camera(camera),
	m_vao(),
	m_size(4),
	m_state(0b1101)
{
	if (!nodes.size()) return;

	std::vector<float> vertices;
	std::vector<uint8_t> vertices_types;

	add_node_vertices(vertices, vertices_types, width, 0, nodes.front().first, nodes.front().second);
	if (nodes.size() > 1) add_node_vertices(vertices, vertices_types, width, 0, nodes.back().first, nodes.back().second);

	const size_t nodes_len = nodes.size();
	for (size_t i = 1; i < nodes_len-1; ++i) {

		const std::pair<int32_t,int32_t> prev = nodes[i-1];
		const std::pair<int32_t,int32_t> curr = nodes[i];
		const std::pair<int32_t,int32_t> next = nodes[i+1];

		const bool prev_up    = curr.second < prev.second;
		const bool prev_down  = curr.second > prev.second;
		const bool prev_left  = curr.first > prev.first;
		const bool prev_right = curr.first < prev.first;

		const bool next_up    = curr.second < next.second;
		const bool next_down  = curr.second > next.second;
		const bool next_left  = curr.first > next.first;
		const bool next_right = curr.first < next.first;

		uint8_t inverse = 0b0001'0000 * (
			(prev_up    && next_right) ||
			(prev_right && next_down)  ||
			(prev_down  && next_left)  ||
			(prev_left  && next_up)    ||
			(prev_down  && next_up)    ||
			(prev_right && next_left)
		);

		uint8_t type = 
			(prev_up    || next_up)    * Direction::UP    +
			(prev_down  || next_down)  * Direction::DOWN  +
			(prev_left  || next_left)  * Direction::LEFT  +
			(prev_right || next_right) * Direction::RIGHT +
			inverse;

		add_node_vertices(vertices, vertices_types, width, type, curr.first, curr.second);

	}

	for (size_t i = 0; i < nodes_len-1; ++i) {
		add_bus_vertices(vertices, vertices_types, width, nodes[i], nodes[i+1]);
	}

	void* data[]       = { vertices.data(), vertices_types.data() };
	uint32_t sizes[]   = { 4, 1 };
	uint32_t types[]   = { GL_FLOAT, GL_UNSIGNED_BYTE };
	uint32_t len       = vertices_types.size();
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
		glUniform2f(m_shader.uniform("offset"), 0,0);
		glUniform4f(m_shader.uniform("off_color"), 0,0.15,0,1);
		glUniform4f(m_shader.uniform("on_color"), 0,0.8,0,1);
		glUniformMatrix4fv(
			m_shader.uniform("viewport"), 1, GL_FALSE, 
			glm::value_ptr(m_camera.getViewport())
		);
		glDrawArrays(GL_TRIANGLES, 0, m_vao.getSize());
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
	m_y(0),
	m_bus_width(1),
	m_bus_size(4)
{

	std::vector<float> vertices;
	std::vector<uint8_t> vertices_types;
	add_node_vertices(vertices, vertices_types, m_bus_width, 0,0,0);

	void* data[]       = { vertices.data(), vertices_types.data() };
	uint32_t sizes[]   = { 4, 1 };
	uint32_t types[]   = { GL_FLOAT, GL_UNSIGNED_BYTE };
	uint32_t len       = 6;
	uint32_t n         = 2;

	m_preview_vao.pushData(data, sizes, types, len, n);

}



void BusFactory::update()
{

	// Get the int coordinate of the cursor.
	float x,y;
	m_camera.getCursorPosition(x,y);
	m_x = static_cast<int32_t>(std::round(x));
	m_y = static_cast<int32_t>(std::round(y));

	// If there are already nodes, force alignment with it.
	if (m_nodes.size()) {
		uint32_t n_x = m_nodes.back().first;
		uint32_t n_y = m_nodes.back().second;
		float dx2 = (n_x-m_x)*(n_x-m_x);
		float dy2 = (n_y-m_y)*(n_y-m_y);
		if (dx2 > dy2) m_y = m_nodes.back().second;
		else m_x = m_nodes.back().first;
	}

	// Add or remove nodes as needed.
	if (m_events.left_click()) add_node();
	if (m_events.right_click()) remove_node();

}



void BusFactory::clear()
{
	m_nodes.clear();
	m_preview.reset();
}



std::unique_ptr<Bus> BusFactory::make() const
{
	return std::make_unique<Bus>(m_shader, m_camera, m_nodes, m_bus_size, m_bus_width);
}



void BusFactory::render() const
{

	// Render the preview if there is one.
	if (m_preview) {
		m_preview->render();
	}

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
	m_preview.reset();
	m_preview = make();
}

void BusFactory::remove_node()
{
	if (m_nodes.size()) m_nodes.pop_back();
	m_preview.reset();
	if (m_nodes.size()) m_preview = make();
}
