#pragma once

class VertexBuffer
{
private:
	unsigned int ID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};