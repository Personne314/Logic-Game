#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../graphics/objects/shader.h"
#include "../../graphics/objects/vao.h"
#include "../../graphics/camera.h"
#include "../../utils/constants.hpp"



class Bus
{
public:

	Bus(const Shader &shader, const Camera &camera);
	~Bus();

	void render();

	void setState(uint32_t id);
	void resetState(uint32_t id);

	bool getState(uint32_t id);
	uint32_t getSize() const { return m_size; }

private:

	const Shader &m_shader;	// The shader to use for render.
	const Camera &m_camera;	// The camera of the associated grid.
	VAO m_vao;	// VAO of the buffer.

	uint32_t m_size;	// Number of wires in the bus.
	uint32_t m_state;	// State of each wire.

};
