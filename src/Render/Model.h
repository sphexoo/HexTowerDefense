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
	void LoadVertices(std::vector<float>& vertices, std::vector<unsigned int> indices, unsigned int iuSlot0, unsigned int iuSlot1, unsigned int iuSlot2);
	void Draw(Renderer& renderer, glm::mat4& viewMatrix, glm::mat4& modelMatrix);
	void DrawDepth(Renderer& renderer, glm::mat4& viewMatrix, glm::mat4& modelMatrix);
	void ModifyVB(std::vector<float>& vertices);
};