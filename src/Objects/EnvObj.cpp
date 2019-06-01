#include "EnvObj.h"
#include "Playfield.h"

EnvObj::EnvObj(Playfield* playfield, Type type, glm::vec3 pos)
	: playfield(playfield)
{
	if (type == TREE)
	{
		model.LoadPly("res/models/tree.ply");
	}
	
	this->pos = pos;
	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

EnvObj::~EnvObj()
{

}

void EnvObj::Update()
{
	// passive object
}
