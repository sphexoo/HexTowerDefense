#include <GL/glew.h>

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	/* Vertex Buffer */
	// Generates a Buffer for vertices which is beeing pointed at by uint pointer buffer
	glGenBuffers(1, &ID);
	// Binds that buffer as current buffer (all following actions will be performed with the currently binded buffer)
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Assignes data to the buffer (Buffer type, length of buffer in memory, data, draw type)
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);


}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
