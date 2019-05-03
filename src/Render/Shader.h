#pragma once
#include <unordered_map>

#include "glm.hpp"

class Shader
{
private:
	struct ShaderPrograms
	{
		std::string vertexShader;
		std::string fragmentShader;
	};
	std::unordered_map<std::string, int> uniform_loc_cache;

	static ShaderPrograms ParseShader(const std::string& path_vs, const std::string& path_fs);
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);

public:
	unsigned int ID;

	Shader(const std::string& vs_frompath, const std::string& fs_frompath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name, float r, float g, float b, float a);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix);
};