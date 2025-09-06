#pragma once

#include <GL/glew.h>



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
	void pushData(void** data, int* sizes, int* type_sizes, 
		int buffer_len, int n);

	int getSize() const { return m_size; }

	void glBind() const { glBindBuffer(GL_ARRAY_BUFFER, m_vbo); }
	void glUnbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:

	uint32_t m_vbo;	// ID of the VBO.
	int m_size;		// Size of the VBO (in number of vectors).

};
