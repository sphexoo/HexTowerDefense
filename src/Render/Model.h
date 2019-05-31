#pragma once
#include <string>
#include <vector>

#include "Renderer.h"

class Model
{
private:
	std::string filepath;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexAttributes* va;

public:
	Model();
	~Model();

	void LoadObj(std::string filepath);
	void LoadPly(std::string filepath);
	void Draw(Renderer& renderer, Shader& shader, glm::mat4& viewMatrix, glm::mat4& modelMatrix);
};