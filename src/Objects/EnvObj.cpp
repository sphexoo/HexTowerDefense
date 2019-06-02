#include "EnvObj.h"
#include "Playfield.h"

EnvObj::EnvObj(Playfield* playfield, Type type, glm::vec3 pos)
	: playfield(playfield)
{
	if (type == TREE)
	{
		model.LoadPly("res/models/tree1.ply");
	}
	else if (type == STONE)
	{
		model.LoadPly("res/models/stones1.ply");
	}
	
	this->pos = pos;
	modelMatrix = glm::translate(glm::mat4(1.0f), pos);

	float angle = ((double)rand() / (RAND_MAX)) * 2.0f * (float)M_PI;
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

EnvObj::~EnvObj()
{

}

void EnvObj::Update()
{
	// passive object
}
