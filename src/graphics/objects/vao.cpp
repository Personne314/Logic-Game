#include "vao.h"



/**
 * @brief Return the size of the type in bytes.
 */
int32_t sizeFromGLType(uint32_t type) {
	switch (type) {
	case GL_FLOAT:	return sizeof(float);
	case GL_DOUBLE:	return sizeof(double);
	case GL_INT:	return sizeof(uint32_t);
	case GL_SHORT:	return sizeof(uint16_t);
	default:		
		print_error("Unknown GLType " + std::to_string(type));
		return -1;
	}
}



/**
 * @brief Construct a VAO.
 */
VAO::VAO() {
	glGenVertexArrays(1, &m_vao);
}

/**
 * @brief Destroy a VAO.
 */
VAO::~VAO() {
	if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);
}



/**
 * @brief Clear the content of the VAO.
 */
void VAO::clean() {
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
void VAO::pushData(void** data, uint32_t* sizes, uint32_t* gl_types, uint32_t buffer_len, uint32_t n) {
	clean();

	// Create a VAO and push the data to the VBO.
	uint32_t type_sizes[n];
	for (uint32_t i = 0; i < n; i++) type_sizes[i] = sizeFromGLType(gl_types[i]);
	m_vbo.pushData(data, sizes, type_sizes, buffer_len, n);

	// Link the VAO to the VBO.
	glBind();
		m_vbo.glBind();
			uint32_t offset = 0;
			for (uint32_t i = 0; i < n; i++) {
				glVertexAttribPointer(i, sizes[i], gl_types[i], GL_FALSE, 0, (void*)(offset));
				glEnableVertexAttribArray(i);
				offset += sizes[i] * type_sizes[i] * buffer_len;
			}
		m_vbo.glUnbind();
	glUnbind();

}
