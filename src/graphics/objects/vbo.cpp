#include "vbo.h"



/**
 * @brief Construct a VBO.
 */
VBO::VBO() : m_size(0)
{
	glGenBuffers(1, &m_vbo);
}

/**
 * @brief Destroy a VBO.
 */
VBO::~VBO()
{
	if(glIsBuffer(m_vbo) == GL_TRUE) glDeleteBuffers(1, &m_vbo);
}



/**
 * @brief Clean the VBO content.
 */
void VBO::clean()
{
	if(glIsBuffer(m_vbo) == GL_TRUE) glDeleteBuffers(1, &m_vbo);
	glGenBuffers(1, &m_vbo);
	m_size = 0;
}



/**
 * @brief Send data to the VBO.
 * @param data List of all data to send.
 * @param sizes Sizes of the vectors in data (dimension).
 * @param type_sizes Sizes of the types of lists in data (bytes).
 * @param buffer_len Number of vectors in each list of data.
 * @param n Number of lists in data.
 */
void VBO::pushData(void** data, uint32_t* sizes, uint32_t* type_sizes, uint32_t buffer_len, uint32_t n)
{
	clean();
	m_size = buffer_len;

	// Calculate all list size and total buffer size.
	GLsizeiptr data_sizes[n+1];
	data_sizes[n] = 0;
	for (uint32_t i = 0; i < n; i++) {
		GLsizeiptr val = sizes[i] * type_sizes[i] * buffer_len;
		data_sizes[n] += val;
		data_sizes[i] = val;
	}

	// Bind the VBO and send alla data to it.
	bind();
		GLsizeiptr offset = 0;
		glBufferData(GL_ARRAY_BUFFER, data_sizes[n], 0, GL_STATIC_DRAW);
		for(uint32_t i = 0; i < n; i++) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, data_sizes[i], data[i]);
			offset += data_sizes[i];
		}
	unbind();
	
}
