#include <GL/glew.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "glm.hpp"
#include "Shader.h"
#include "Logger.h"

/* Access the logger object globally created in Application.cpp */
extern Logger logger;

Shader::Shader(const std::string& vs_frompath, const std::string& fs_frompath)
{
	/* Constructor creates vertex and fragment shader and installs both */
	ShaderPrograms parsed = ParseShader(vs_frompath, fs_frompath);
	ID = CreateShader(parsed.vertexShader, parsed.fragmentShader);
}

Shader::~Shader()
{
	/* Deletes the currently installed shaders */
	glDeleteProgram(ID);
}

void Shader::Bind() const
{
	glUseProgram(ID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

Shader::ShaderPrograms Shader::ParseShader(const std::string& path_vs, const std::string& path_fs)
{
	std::stringstream vertexShader;
	std::stringstream fragmentShader;
	std::string line;

	std::ifstream stream_vs(path_vs);
	while (getline(stream_vs, line))
	{
		vertexShader << line << "\n";
	}
	logger.log("Vertex shader parsed", logger.Info);
	
	std::ifstream stream_fs(path_fs);
	while (getline(stream_fs, line))
	{
		fragmentShader << line << "\n";
	}
	logger.log("Fragment shader parsed", logger.Info);

	return { vertexShader.str(), fragmentShader.str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	/* Takes shader type and source code.
	   Returns an id which can be used to reference to the compiled shader */

	   // Shader object of specified type which can be referenced by returned uint
	unsigned int id = glCreateShader(type);
	// Pointer to beginning of source code
	const char* src = &source[0];
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		logger.log("Shader compilaton failed", logger.Error);
		logger.log(message, logger.Error);
		glDeleteShader(id);
		return 0;
	}
	else
	{
		logger.log("Shader compilation successful", logger.Info);
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	/* Takes strings with source code for vertex and fragment shaders.
	   Returns the compiled and linked shader program containing both, vertex and fragment shader */

	   // Creates an empty program object which can be referred to by using the returned uint
	unsigned int program = glCreateProgram();
	// Compile vertex and fragemnt shader
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// Attaches both compiled shader objects to the empty project object
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	// Links all compiled files
	glLinkProgram(program);
	// Checks if the created shader .exe can run with current OpenGL configuration
	glValidateProgram(program);

	// Deleting shader objects
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (uniform_loc_cache.find(name) != uniform_loc_cache.end())
	{
		return uniform_loc_cache[name];
	}

	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		logger.log("Uniform location not found", Logger::Warning);
		std::cout << "	Uniform name: '" << name << "'" << std::endl;
	}

	uniform_loc_cache[name] = location;

	return location;
}

void Shader::SetUniform4f(const std::string& name, float r, float g, float b, float a)
{
	int location = GetUniformLocation(name);
	glUniform4f(location, r, g, b, a);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	int location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	int location = GetUniformLocation(name);
	glUniform1f(location, value);
}

void Shader::SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix)
{
	int location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}
