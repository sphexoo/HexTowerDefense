#include <sstream>
#include <fstream>
#include <iostream>

#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"
#include "Model.h"

Model::Model(float x, float y, float z)
{
	pos = glm::vec3(x, y, z);

	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

Model::~Model()
{
	delete vb;
	delete va;
	delete ib;
}

void Model::Load(std::string path)
{	
	this->path = path;

	std::ifstream source(path);

	for (std::string line; std::getline(source, line);) {
		std::istringstream in(line);
		std::string type;
		in >> type;
		if (type == "v")
		{
			float x, y, z;
			in >> x >> y >> z;

			//std::cout << x << ", " << y << ", " << z << std::endl;
			
			vertices.push_back(x * 1.0f);
			vertices.push_back(y * 1.0f);
			vertices.push_back(z * 1.0f);
		}

		if (type == "f")
		{
			unsigned int i1, i2, i3;
			in >> i1 >> i2 >> i3;

			//std::cout << i1 << ", " << i2 << ", " << i3 << std::endl;

			indices.push_back(i1);
			indices.push_back(i2);
			indices.push_back(i3);
		}
	}

	vb = new VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	ib = new IndexBuffer(&indices[0], indices.size());
	va = new VertexAttributes(true, 3, false, 0);
}

void Model::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	renderer.Draw3Dbasic(*vb, *va, *ib, shader, viewMatrix, modelMatrix, glm::vec4(1.0f, 1.0f, 0.6f, 1.0f));
}