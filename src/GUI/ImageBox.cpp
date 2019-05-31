#include "ImageBox.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexAttributes.h"
#include "Texture.h"

ImageBox::ImageBox(float x, float y, float z, float scale, std::string path)
{
	texture = new Texture(path);

	this->fWidth = (float)texture->GetWidth();
	this->fHeight = (float)texture->GetHeight();
	this->scale *= scale;

	pos = glm::vec3(x, y, z);
	
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

ImageBox::~ImageBox()
{
	delete vb;
	delete ib;
	delete va;
	delete texture;
}