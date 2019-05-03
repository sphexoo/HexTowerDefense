#pragma once
#include "ScreenElement.h"
#include "Renderer.h"

class ImageBox : public ScreenElement
{
	typedef void(*handlerFcn)(int state);
public:
	ImageBox(float x, float y, std::string path, handlerFcn handlerFcn, int handleToValue);
	~ImageBox();
};