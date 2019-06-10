#pragma once

class VertexAttributes
{
private:
	unsigned int uiSlot0;
	unsigned int uiSlot1;
	unsigned int uiSlot2;

public:
	VertexAttributes(unsigned int uiSlot0, unsigned int uiSlot1 = 0, unsigned int uiSlot2 = 0);
	void Bind() const;
};