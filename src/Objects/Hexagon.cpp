#include "Hexagon.h"

#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"
#include "Texture.h"

Hexagon::Hexagon()
{
	modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 100.0f));

	vb = new VertexBuffer(vertices, sizeof(float) * 35);
	ib = new IndexBuffer(indices, 18);
	va = new VertexAttributes(true, 3, true, 2);

	texture = new Texture("res/textures/hex.png");
}

Hexagon::~Hexagon()
{
	delete vb;
	delete va;
	delete ib;
}

void Hexagon::Draw(Renderer& renderer, Shader& shader)
{
	texture->Bind();
	renderer.Draw2D(*vb, *va, *ib, shader, modelMatrix);
}

void Hexagon::Rotate()
{
	modelMatrix = glm::rotate(modelMatrix, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
}