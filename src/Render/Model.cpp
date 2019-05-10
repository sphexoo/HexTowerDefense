#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"
#include "Model.h"

#define _USE_MATH_DEFINES 
#include <math.h>

Model::Model(float x, float y, float z)
{
	pos = glm::vec3(x, y, z);

	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
	modelMatrix = glm::rotate(modelMatrix, (float)M_PI * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
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

	std::vector<float> tmp_coords;
	std::vector<float> tmp_normals;
	std::vector<unsigned int> tmp_indices;
	std::vector<unsigned int> tmp_faces;

	std::ifstream source(path);

	for (std::string line; std::getline(source, line);) {
		std::istringstream in(line);
		std::string type;
		in >> type;
		if (type == "v")
		{
			float x, y, z;
			in >> x >> y >> z;
			
			tmp_coords.push_back(x);
			tmp_coords.push_back(y);
			tmp_coords.push_back(z);
		}
		else if (type == "vn")
		{
			float x, y, z;
			in >> x >> y >> z;

			tmp_normals.push_back(x);
			tmp_normals.push_back(y);
			tmp_normals.push_back(z);
		}
		else if (type == "f")
		{
			std::string norm = in.str();
			std::replace(norm.begin(), norm.end(), '/', ' ');
			std::replace(norm.begin(), norm.end(), 'f', ' ');

			std::istringstream n(norm);

			unsigned int i00, i01, i02, i10, i11, i12;
			n >> i00 >> i01 >> i02 >> i10 >> i11 >> i12;
			tmp_indices.push_back(i00 - 1);
			tmp_faces.push_back(i01 - 1);
			tmp_indices.push_back(i02 - 1);
			tmp_faces.push_back(i10 - 1);
			tmp_indices.push_back(i11 - 1);
			tmp_faces.push_back(i12 - 1);
		}
	}

	for (unsigned int i = 0; i < tmp_indices.size(); i++)
	{
		indices.push_back(i);
		vertices.insert(vertices.end(), tmp_coords.begin() + tmp_indices[i] * 3, tmp_coords.begin() + tmp_indices[i] * 3 + 3);
		vertices.insert(vertices.end(), tmp_normals.begin() + tmp_faces[i] * 3, tmp_normals.begin() + tmp_faces[i] * 3 + 3);
	}

	vb = new VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	ib = new IndexBuffer(&indices[0], indices.size());
	va = new VertexAttributes(true, 3, true, 3);
}

void Model::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	renderer.Draw3Dlight(*vb, *va, *ib, shader, viewMatrix, modelMatrix, glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
}