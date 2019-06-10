#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "GL/glew.h"

#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"
#include "Model.h"

#define _USE_MATH_DEFINES 
#include <math.h>

Model::Model()
{

}

Model::~Model()
{
	delete vb;
	delete va;
	delete ib;
}

void Model::LoadObj(std::string filepath)
{	
	this->filepath = filepath;

	std::vector<float> tmp_coords;
	std::vector<float> tmp_normals;
	std::vector<unsigned int> tmp_indices;
	std::vector<unsigned int> tmp_faces;

	std::ifstream source(filepath);

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
	va = new VertexAttributes(true, 3, true, 3, false, 0);

	vertices.clear();
	indices.clear();
}

void Model::LoadPly(std::string filepath)
{
	/* loads model data from .ply file */
	this->filepath = filepath;

	std::ifstream source(filepath);
	// number of vertices and faces left to parse (based on header information)
	int iVerticesLeft, iFacesLeft;
	// number of data per vertex (based on header information)
	int iDataPerVertex = 0;
	bool isHeader = true;
	std::string sTemp;

	for (std::string line; std::getline(source, line);)
	{
		std::istringstream linestream(line);
		
		// parsing header line
		if (isHeader)
		{
			linestream >> sTemp;

			if (sTemp == "element")
			{
				linestream >> sTemp;

				if (sTemp == "vertex")
				{
					linestream >> iVerticesLeft;
				}
				else if (sTemp == "face")
				{
					linestream >> iFacesLeft;
				}
			}
			else if (sTemp == "property")
			{	
				linestream >> sTemp;
				// check if property describes vertices
				if (sTemp != "list")
				{
					iDataPerVertex++;
				}
			}
			else if (sTemp == "end_header")
			{
				// following lines are no header information but actual vertices. 
				isHeader = false;
				// reserve space for vertices and indices array (for indices it is assumed that there is 3 indices per face)
				vertices.reserve(iVerticesLeft * iDataPerVertex);
				indices.reserve(iFacesLeft * 3);
			}
		}
		// parsing vertex line
		else
		{
			if (iVerticesLeft > 0)
			{
				// loop through one single vertex
				for (int i = 0; i < iDataPerVertex; i++)
				{
					float fVertexData;
					linestream >> fVertexData;
					// normalize color data of parsed vertex
					if (i > 5)
					{
						fVertexData = fVertexData / 255.0f;
					}
					vertices.push_back(fVertexData);
				}
				iVerticesLeft--;
			}
			else if (iFacesLeft > 0)
			{
				// get actual number of indices per face
				unsigned int uiIndicesPerFace;
				linestream >> uiIndicesPerFace;
				for (unsigned int i = 0; i < uiIndicesPerFace; i++)
				{
					unsigned int uiIndexData;
					linestream >> uiIndexData;
					indices.push_back(uiIndexData);
				}
				iFacesLeft--;
			}
		}
	}

	vb = new VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	ib = new IndexBuffer(&indices[0], indices.size());
	va = new VertexAttributes(true, 3, true, 3, true, 3);
}

void Model::LoadVertices(std::vector<float>& vertices, std::vector<unsigned int> indices)
{
	vb = new VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	ib = new IndexBuffer(&indices[0], indices.size());
	va = new VertexAttributes(true, 3, true, 3, true, 3);
}

void Model::Draw(Renderer& renderer, Shader& shader, glm::mat4& viewMatrix, glm::mat4& modelMatrix)
{
	renderer.Draw3Dobject(*vb, *va, *ib, shader, viewMatrix, modelMatrix);
}


void Model::ModifyVB(std::vector<float>& vertices)
{
	vb->Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
}