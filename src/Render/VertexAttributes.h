#pragma once

class VertexAttributes
{
private:
	unsigned int vPos;
	unsigned int vTexPos;
	bool enablePos;
	bool enableTexPos;

public:
	VertexAttributes(bool enablePos, unsigned int vPos, bool enableTexPos /* = false*/, unsigned int vTexPos /* = 0*/);
	void Bind() const;
};