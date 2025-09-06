#pragma once

#include <GL/glew.h>
#include <stdint.h>

#include "vbo.h"



/**
 * @class VAO
 * @brief Wrapper class arround OpenGL VAO.
 */
class VAO
{
public :

	VAO();
	~VAO();

	void clean();
	void pushData(void** data, uint32_t* sizes, uint32_t* gl_types, uint32_t buffer_len, uint32_t n);

	uint32_t getSize() const { return m_vbo.getSize(); }

	void glBind() const { glBindVertexArray(m_vao); }
	void glUnbind() const { glBindVertexArray(0); }

private:

	GLuint m_vao;	// The id of the VAO.
	VBO m_vbo;		// The VBO of this VAO.

};
