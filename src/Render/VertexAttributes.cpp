#include <GL/glew.h>

#include "VertexAttributes.h"

VertexAttributes::VertexAttributes(unsigned int uiSlot0, unsigned int uiSlot1 /*= 0*/, unsigned int uiSlot2 /*= 0*/)
	: uiSlot0(uiSlot0), uiSlot1(uiSlot1), uiSlot2(uiSlot2)
{

}

void VertexAttributes::Bind() const
{
	// Enables an Attribute Array for the currently bound buffer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, uiSlot0, GL_FLOAT, GL_FALSE, sizeof(float) * (uiSlot0 + uiSlot1 + uiSlot2), nullptr);
	/*glVertexAttribPointer(index of data within one vertex,
							number of values of vertex segment,
							data type of values of vertex segment,
							normalize?,
							length of one vertex in bytes,
							relative offset of specified vertex data within one vertex); */

	// check if second vertex attribute is specified
	if (uiSlot1 > 0)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, uiSlot1, GL_FLOAT, GL_FALSE, sizeof(float) * (uiSlot0 + uiSlot1 + uiSlot2), (const void*)(sizeof(float) * uiSlot0));
		
		// check if third vertex attribute is specified
		if (uiSlot2 > 0)
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, uiSlot2, GL_FLOAT, GL_FALSE, sizeof(float) * (uiSlot0 + uiSlot1 + uiSlot2), (const void*)(sizeof(float) * (uiSlot0 + uiSlot1)));
		}
	}
}