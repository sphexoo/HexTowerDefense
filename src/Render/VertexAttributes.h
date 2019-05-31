#pragma once

class VertexAttributes
{
private:
	unsigned int uiSlot1;
	unsigned int uiSlot2;
	unsigned int uiSlot3;
	bool bSlot1;
	bool bSlot2;
	bool bSlot3;

public:
	VertexAttributes(bool bSlot1, unsigned int uiSlot1, bool bSlot2 /*= false*/, unsigned int uiSlot2 /*= 0*/, bool bSlot3 /*= false*/, unsigned int uiSlot3 /*= 0*/);
	void Bind() const;
};