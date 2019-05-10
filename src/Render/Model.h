#pragma once
#include <string>
#include <vector>

#include "Renderer.h"

class Model
{
private:
	std::string path;
	glm::vec3 pos;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::vec4 color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexAttributes* va;

public:
	Model(float x, float y, float z);
	~Model();

	void Load(std::string path);
	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	void SetColor(float r, float g, float b, float a); 
};