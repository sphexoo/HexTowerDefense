#include "Hexagon.h"

#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

Hexagon::Hexagon(float x, float y, float z, glm::vec4 color)
	:color(color)
{
	pos = glm::vec3(x, y, z);
	modelMatrix = glm::translate(glm::mat4(1.0f), pos);

	vb = new VertexBuffer(vertices, sizeof(float) * 21);
	ib = new IndexBuffer(indices, 18);
	va = new VertexAttributes(true, 3, false, 0);
}

Hexagon::~Hexagon()
{
	delete vb;
	delete va;
	delete ib;
}

void Hexagon::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	shader.SetUniform4f("u_Color", color.x, color.y, color.z, color.w);
	renderer.Draw3D(*vb, *va, *ib, shader, viewMatrix, modelMatrix);
}

void Hexagon::SetColor(float r, float g, float b, float a)
{
	color = glm::vec4(r, g, b, a);
}