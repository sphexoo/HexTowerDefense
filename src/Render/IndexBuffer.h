#pragma once

class IndexBuffer
{
private:
	unsigned int ID;
	unsigned int count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;
};