#pragma once
#include "ScreenElement.h"
#include "Renderer.h"

class ButtonBox : public ScreenElement
{
private:
	typedef void(*handlerFcn)(int state);
public:
	ButtonBox(float x, float y, std::string path, fcnPtr handlerFcn, int handleToValue);
	~ButtonBox();
};