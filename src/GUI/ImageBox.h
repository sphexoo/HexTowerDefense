#pragma once
#include "ScreenElement.h"
#include "Renderer.h"

class ImageBox : public ScreenElement
{
public:
	ImageBox(float x, float y, float z, float scale, std::string path);
	~ImageBox();
};