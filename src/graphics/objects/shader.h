#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include <stdint.h>

#include "../../utils/logger.h"



/**
 * @class Shader
 * @brief Load and compile a shader from the disk. 
 */
class Shader
{
public:

	Shader(const std::string& name);
	~Shader();

	void use() const { glUseProgram(m_progID); }

	int getUniformLocation(std::string name) const { return glGetUniformLocation(m_progID, name.c_str()); }

	bool isInit() const { return m_init; }

private:

	bool compileShader(uint32_t& shader, GLenum type, const std::string& source);

	bool m_init;	// true if the shader is well initialized.

	uint32_t m_vertID;	// Vertex shader id.
	uint32_t m_fragID;	// Framgent shader id.
	uint32_t m_progID;	// Program id.

};
