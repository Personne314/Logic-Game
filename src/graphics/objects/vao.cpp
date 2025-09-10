#include "vao.h"



/**
 * @brief Return the size of the type in bytes.
 * @param type The type to get the size from.
 */
int32_t sizeFromGLType(uint32_t type)
{
	switch (type) {
	case GL_FLOAT:	return sizeof(float);
	case GL_DOUBLE:	return sizeof(double);
	case GL_INT:	return sizeof(int32_t);
	case GL_SHORT:	return sizeof(int16_t);
	case GL_BYTE:	return sizeof(int8_t);
	case GL_UNSIGNED_INT:	return sizeof(uint32_t);
	case GL_UNSIGNED_SHORT:	return sizeof(uint16_t);
	case GL_UNSIGNED_BYTE:	return sizeof(uint8_t);
	default:		
		print_error("Unknown GLType {}", type);
		return -1;
	}
}

/**
 * @brief Return true if the type is an integer type.
 * @param type The type to check.
 */
bool isIntegerType(uint32_t type) {
	switch (type) {
	case GL_BYTE:
	case GL_SHORT:
	case GL_INT:
	case GL_UNSIGNED_BYTE:
	case GL_UNSIGNED_SHORT:
	case GL_UNSIGNED_INT:
		return true;
	default: return false;
	}
}



/**
 * @brief Construct a VAO.
 */
VAO::VAO()
{
	glGenVertexArrays(1, &m_vao);
}

/**
 * @brief Destroy a VAO.
 */
VAO::~VAO()
{
	if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);
}



/**
 * @brief Clear the content of the VAO.
 */
void VAO::clean()
{
	if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);
	glGenVertexArrays(1, &m_vao);
}



/**
 * @brief Send data to the VAO.
 * @param data List of all data to send.
 * @param sizes Sizes of the vectors in data (dimension).
 * @param gl_types Types of the lists vector elements.
 * @param buffer_len Number of vectors in each list of data.
 * @param n Number of lists in data.
 */ 
void VAO::pushData(void** data, uint32_t* sizes, uint32_t* gl_types, uint32_t buffer_len, uint32_t n)
{
	clean();

	// Create a VAO and push the data to the VBO.
	uint32_t type_sizes[n];
	for (uint32_t i = 0; i < n; i++) type_sizes[i] = sizeFromGLType(gl_types[i]);
	m_vbo.pushData(data, sizes, type_sizes, buffer_len, n);

	// Link the VAO to the VBO.
	bind();
		m_vbo.bind();
			size_t offset = 0;
			for (uint32_t i = 0; i < n; i++) {
				if (isIntegerType(gl_types[i])) {
					glVertexAttribIPointer(i, sizes[i], gl_types[i], /* stride */ 0, (void*)(offset));
				} else {
					glVertexAttribPointer(i, sizes[i], gl_types[i], GL_FALSE, 0, (void*)(offset));
				}
				glEnableVertexAttribArray(i);
				offset += sizes[i] * type_sizes[i] * buffer_len;
			}
		m_vbo.unbind();
	unbind();

}
