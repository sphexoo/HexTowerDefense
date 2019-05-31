#include "ButtonBox.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexAttributes.h"
#include "Texture.h"

ButtonBox::ButtonBox(float x, float y, std::string path, fcnPtr handlerFcn, int handleToValue)
{
	texture = new Texture(path);
	this->fWidth = (float)texture->GetWidth();
	this->fHeight = (float)texture->GetHeight();

	//pos = glm::vec3(x + fWidth * 0.5f, y + fHeight * 0.5f, 0.0f);
	pos = glm::vec3(x, y, 0.0f);

	this->fcn = handlerFcn;
	this->handleToValue = handleToValue;

	for (int i = 0; i < 20; i = i + 5)
	{
		vertices[i] = vertices[i] * fWidth;
		vertices[i + 1] = vertices[i + 1] * fHeight;
	}

	vb = new VertexBuffer(&vertices[0], sizeof(float) * 20);
	ib = new IndexBuffer(&indices[0], 6);
	va = new VertexAttributes(true, 3, true, 2, false, 0);

	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

ButtonBox::~ButtonBox()
{
	delete vb;
	delete ib;
	delete va;
	delete texture;
}