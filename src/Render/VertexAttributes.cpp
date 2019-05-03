#include <GL/glew.h>

#include "VertexAttributes.h"

VertexAttributes::VertexAttributes(bool enablePos, unsigned int vPos, bool enableTexPos /* = false*/, unsigned int vTexPos /* = 0*/)
{
	this->vPos = vPos;
	this->vTexPos = vTexPos;
	this->enablePos = enablePos;
	this->enableTexPos = enableTexPos;
}

void VertexAttributes::Bind() const
{
	// Enables an Attribute Array for the currently bound buffer
	glEnableVertexAttribArray(0);
	// Specifies the Attributes for buffer data (start at, number of vertices, data type, normalize e.g. 0 - 255 --> 0.0f - 1.0f, length of one vertice in memory, position of different data inside one vertice)
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(0, vPos, GL_FLOAT, GL_FALSE, sizeof(float) * (vPos + vTexPos), 0);
	//glVertexAttribPointer(index of vertex type, count of vertex type to specify, data type, normalize, length of one vertice in bytes, of specified vertice type from beginning of vertex);

	if (enableTexPos)
	{
		// Enables an Attribute Array for the currently bound buffer
		glEnableVertexAttribArray(1);
		// Specifies the Attributes for buffer data (start at, number of vertices, data type, normalize e.g. 0 - 255 --> 0.0f - 1.0f, length of one vertice in memory, position of different data inside one vertice)
		glVertexAttribPointer(1, vTexPos, GL_FLOAT, GL_FALSE, sizeof(float) * (vPos + vTexPos), (const void*)(sizeof(float) * vPos));
		//glVertexAttribPointer(index of vertex type, count of vertex type, data type, normalize, length of one vertice in bytes, of specified vertice type from beginning of vertex);
	}
}