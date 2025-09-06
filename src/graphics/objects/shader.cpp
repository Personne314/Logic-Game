#include "shader.h"

#include <iostream>
#include <fstream>



/**
 * @brief Construct a shader from source files.
 * @param name The name of the shader. 
 */
Shader::Shader(const std::string& name) :
	m_init(false), 
	m_vertID(0),
	m_fragID(0),
	m_progID(0)
{

	// Get the source files names.
	const std::string vertex = "./GameData/shaders/" + name + ".vert";
	const std::string fragment = "./GameData/shaders/" + name + ".frag";

	// Compile the sources.
	if (!compileShader(m_vertID, GL_VERTEX_SHADER, vertex) ||
		!compileShader(m_fragID, GL_FRAGMENT_SHADER, fragment)
	) return;

	// Create the program.
	m_progID = glCreateProgram();
	glAttachShader(m_progID, m_vertID);
	glAttachShader(m_progID, m_fragID);

	// Link the program.
	glLinkProgram(m_progID);
	GLint state = 0;
	glGetProgramiv(m_progID, GL_LINK_STATUS, &state);
	if(state != GL_TRUE) {

		// Get error message.
		GLint size = 0;
		glGetProgramiv(m_progID, GL_INFO_LOG_LENGTH, &size);
		char *error = new char[size + 1];
		glGetShaderInfoLog(m_progID, size, &size, error);
		error[size] = '\0';

		// Log the error.
		print_error("Failed to link the shader '" + name + "' : " + std::string(error));
		delete[] error;
		return;

	}

	// The shader is now usable.
	m_init = true;

}

/**
 * @brief Destruct a shader.
 */
Shader::~Shader() {
	if(glIsShader(m_vertID) == GL_TRUE) glDeleteShader(m_vertID);
	if(glIsShader(m_fragID) == GL_TRUE) glDeleteShader(m_fragID);
	if(glIsProgram(m_progID) == GL_TRUE) glDeleteProgram(m_progID);
}



/**
 * @brief Compile a shader source code.
 * @param shader The variable where to store the shader id.
 * @param type The type of the shader to compile.
 * @param source The source file path of the shader.
 */
bool Shader::compileShader(uint32_t& shader, GLenum type, const std::string& source) {

	// Create a new shader.
	shader = glCreateShader(type);
	if (shader == 0) {
		print_error("Failed to compile '" + source + "' : type " + std::to_string(type) + " does not exists.");
		return false;
	} 

	// Open the file.   
	std::ifstream file(source.c_str());
	if (!file) {
		print_error("Failed to compile '" + source + "' : source file does not exists.");
		return false;
	} 

	// Read the source code.
	std::string sourceCode, line;
	while (getline(file, line)) sourceCode += line;
	file.close();

	// Compile the shader.
	const GLchar* charSourceCode = sourceCode.c_str();
	glShaderSource(shader, 1, &charSourceCode, 0);
	glCompileShader(shader);
	GLint state = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &state);
	if (state != GL_TRUE) {

		// Get error messages.
		GLint size = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
		char *error = new char[size + 1];
		glGetShaderInfoLog(shader, size, &size, error);
		error[size] = '\0';

		// Log the error.
		print_error("Failed to compile '" + source + "' : " + std::string(error));
		delete [] error;
		return false;

	}

	// The shader is now compiled.
	return true;

}
