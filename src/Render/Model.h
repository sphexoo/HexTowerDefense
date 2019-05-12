#pragma once
#include <string>
#include <vector>

#include "Renderer.h"

class Model
{
private:
	std::string filepath;
	glm::vec4 color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexAttributes* va;

public:
	Model();
	~Model();

	void Load(std::string filepath);
	void Draw(Renderer& renderer, Shader& shader, glm::mat4& viewMatrix, glm::mat4& modelMatrix);
	void SetColor(float r, float g, float b, float a); 
};