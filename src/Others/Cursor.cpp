#include <iostream>

#include "Cursor.h"
#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Input.h"

extern Input input;

Cursor::Cursor(glm::vec3 pos)
	: pos(pos)
{
	vb = new VertexBuffer(vertices, sizeof(float) * 20);
	ib = new IndexBuffer(indices, 6);
	va = new VertexAttributes(true, 3, true, 2);

	modelMatrix = glm::translate(glm::mat4(1.0f), pos);

	texture = new Texture("res/textures/cursor.png");
}

Cursor::~Cursor()
{
	delete vb;
	delete va;
	delete ib;
	delete texture;
}

void Cursor::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	renderer.Draw3Dtexture(*vb, *va, *ib, shader, viewMatrix, modelMatrix, *texture);
}

void Cursor::Update()
{
	pos.x += (Input::mX - prevmX) * fSpeed;
	pos.y -= (Input::mY - prevmY) * fSpeed;

	prevmX = Input::mX;
	prevmY = Input::mY;

	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}