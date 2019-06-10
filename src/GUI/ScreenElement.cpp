#include "ScreenElement.h"
#include "Texture.h"

ScreenElement::ScreenElement()
{
	/*Contructs new ScreenElement object*/
}

ScreenElement::~ScreenElement()
{
	/*Destructs existing ScreenElement object*/
}

void ScreenElement::Draw(Renderer& renderer)
{
	/*Calls DrawGui function of renderer for this ScreenElement object*/
	if (draw)
	{
		texture->Bind();
		renderer.Draw2Dtexture(*vb, *va, *ib, modelMatrix, *texture, fColorScale);
	}
}

void ScreenElement::OnClick()
{
	/*Calls click event function if one is specified and passes specified value to it*/
	if (fcn != nullptr)
	{
		fcn(handleToValue);
	}
}

void ScreenElement::OnHover()
{
	/*Performs actions if mouse cursor hovers over ScreenElement*/
	fColorScale = 0.5f;

}

void ScreenElement::OnNoHover()
{
	/*Performs actions if mouse cursor hovers over ScreenElement*/
	fColorScale = 1.0f;

}

void ScreenElement::Move(float x, float y)
{
	pos.x += x; 
	pos.y += y;
	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}