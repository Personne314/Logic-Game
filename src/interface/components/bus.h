#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <memory>
#include <vector>
#include <utility>
#include <cmath>

#include "../../graphics/objects/shader.h"
#include "../../graphics/objects/vao.h"
#include "../../graphics/camera.h"
#include "../../utils/events.h"
#include "../../utils/constants.hpp"



class BusFactory;
class Bus
{
public:

	~Bus();

	void render();

	void setState(uint32_t id);
	void resetState(uint32_t id);

	bool getState(uint32_t id);
	uint32_t getSize() const { return m_size; }

	friend class BusFactory;

private:

	Bus(
		const Shader &shader, 
		const Camera &camera, 
		const std::vector<std::pair<int32_t, int32_t>> &nodes, 
		uint32_t size
	);

	const Shader &m_shader;	// The shader to use for render.
	const Camera &m_camera;	// The camera of the associated grid.
	VAO m_vao;	// VAO of the buffer.

	const uint32_t m_size;	// Number of wires in the bus.
	uint32_t m_state;	// State of each wire.

};



class BusFactory
{
public:

	BusFactory(const Shader &shader, const Camera &camera, const Events &events);
	~BusFactory();

	void update();
	void clear();

	std::unique_ptr<Bus> make() const;

	void render() const;

private:

	const Shader &m_shader;	// The shader to use for render.
	const Camera &m_camera;	// The camera of the associated grid.
	const Events &m_events;	// The game events handler.

	void add_node();
	void remove_node();
	void update_preview();

	std::vector<std::pair<int32_t, int32_t>> m_nodes;	// Nodes of the bus.
	std::unique_ptr<Bus> m_preview;	// Preview bus.
	VAO m_preview_vao;	// VAO for the preview node.

	int32_t m_x;	// Cursor x closed valid node position.
	int32_t m_y;	// Cursor y closed valid node position.

};

