#pragma once

#include <GL/glew.h>
#include <stdint.h>
#include <string>

#include "../../utils/logger.hpp"



/**
 * @class VBO
 * @brief Wrapper arround an OpenGL VBO
 */
class VBO
{
public:

	VBO();
	~VBO();

	void clean();
	void pushData(void** data, uint32_t* sizes, uint32_t* type_sizes, uint32_t buffer_len, uint32_t n);

	uint32_t getSize() const { return m_size; }

	void bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_vbo); }
	void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:

	uint32_t m_vbo;		// ID of the VBO.
	uint32_t m_size;	// Size of the VBO (in number of vectors).

};
