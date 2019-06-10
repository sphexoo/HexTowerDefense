#include <GL/glew.h>

#include "VertexAttributes.h"

VertexAttributes::VertexAttributes(bool bSlot1, unsigned int uiSlot1, bool bSlot2 = false, unsigned int uiSlot2 = 0, bool bSlot3 = false, unsigned int uiSlot3 = 0)
	: bSlot1(bSlot1), bSlot2(bSlot2), bSlot3(bSlot3), uiSlot1(uiSlot1), uiSlot2(uiSlot2), uiSlot3(uiSlot3)
{

}

void VertexAttributes::Bind() const
{
	// Enables an Attribute Array for the currently bound buffer
	glEnableVertexAttribArray(0);
	// Specifies the Attributes for buffer data (start at, number of vertices, data type, normalize e.g. 0 - 255 --> 0.0f - 1.0f, length of one vertice in memory, position of different data inside one vertice)
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(0, uiSlot1, GL_FLOAT, GL_FALSE, sizeof(float) * (uiSlot1 + uiSlot2 + uiSlot3), nullptr);
	//glVertexAttribPointer(index of vertex type, count of vertex type to specify, data type, normalize, length of one vertice in bytes, of specified vertice type from beginning of vertex);

	if (bSlot2)
	{
		// Enables an Attribute Array for the currently bound buffer
		glEnableVertexAttribArray(1);
		// Specifies the Attributes for buffer data (start at, number of vertices, data type, normalize e.g. 0 - 255 --> 0.0f - 1.0f, length of one vertice in memory, position of different data inside one vertice)
		glVertexAttribPointer(1, uiSlot2, GL_FLOAT, GL_FALSE, sizeof(float) * (uiSlot1 + uiSlot2 + uiSlot3), (const void*)(sizeof(float) * uiSlot1));
		//glVertexAttribPointer(index of vertex type, count of vertex type, data type, normalize, length of one vertice in bytes, of specified vertice type from beginning of vertex);

		if (bSlot3)
		{
			// Enables an Attribute Array for the currently bound buffer
			glEnableVertexAttribArray(2);
			// Specifies the Attributes for buffer data (start at, number of vertices, data type, normalize e.g. 0 - 255 --> 0.0f - 1.0f, length of one vertice in memory, position of different data inside one vertice)
			glVertexAttribPointer(2, uiSlot3, GL_FLOAT, GL_FALSE, sizeof(float) * (uiSlot1 + uiSlot2 + uiSlot3), (const void*)(sizeof(float) * (uiSlot1 + uiSlot2)));
			//glVertexAttribPointer(index of vertex type, count of vertex type, data type, normalize, length of one vertice in bytes, of specified vertice type from beginning of vertex);
		}
	}
}