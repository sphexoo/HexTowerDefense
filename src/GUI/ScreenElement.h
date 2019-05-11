#pragma once
#include <vector>
#include "Renderer.h"

typedef void(*fcnPtr)(int state); // function pointer which holds function which is called when click event is registered

class ScreenElement
{
	/*Base class for elements which are drawn onto a screen.
	Actual element implementations can inherit base functionality from this class*/
public:
	float fColorScale = 1.0f;
	bool draw = true;
	glm::vec3 pos;
	float fWidth, fHeight; // size of screen element
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);	   // scale of screen element based on size
	float scaleMax = 1.2f;  // max scale of screen element based on size
	float scaleMin = 1.0f;  // max scale of screen element based on size

	glm::mat4 modelMatrix;

	std::vector<float> vertices =  { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
									  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
									  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
									 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f }; // basic vector for vertices of rectangular screen element

	std::vector<unsigned int> indices = { 0, 1, 2,
									      2, 3, 0 }; // basic vector for indices of rectangular screen element

	fcnPtr fcn = nullptr; // this function is called when element is pressed
	int handleToValue = 0; // value which is passed to function specfied above

	VertexBuffer* vb; // Pointers to render objects of screen element
	IndexBuffer* ib;
	VertexAttributes* va;

	Texture* texture; //Pointer to texture of screen element

public:
	ScreenElement();
	~ScreenElement();
	void Draw(Renderer& renderer, Shader& shader);
	void OnClick();
	void OnHover();
	void OnNoHover();
	void Move(float x, float y);
};