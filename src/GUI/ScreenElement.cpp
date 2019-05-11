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

void ScreenElement::Draw(Renderer& renderer, Shader& shader)
{
	/*Calls DrawGui function of renderer for this ScreenElement object*/
	if (draw)
	{
		texture->Bind();
		renderer.Draw2Dtexture(*vb, *va, *ib, shader, modelMatrix, *texture);
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
	if (scale.x < scaleMax)
	{
		scale += glm::vec3(0.01f, 0.01f, 0.0f);
	}
}

void ScreenElement::OnNoHover()
{
	/*Performs actions if mouse cursor hovers over ScreenElement*/
	if (scale.x > scaleMin)
	{
		scale -= glm::vec3(0.01f, 0.01f, 0.0f);
	}
}

void ScreenElement::Move(float x, float y)
{
	pos.x += x; 
	pos.y += y;
	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}