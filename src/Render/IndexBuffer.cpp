#include <GL/glew.h>

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	this->count = count;

	/* Vertex Buffer */
	// Generates a Buffer for vertices which is beeing pointed at by uint pointer buffer
	glGenBuffers(1, &ID);
	// Binds that buffer as current buffer (all following actions will be performed with the currently binded buffer)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	// Assignes data to the buffer (Buffer type, length of buffer in memory, data, draw type)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetCount() const
{
	return count;
}
