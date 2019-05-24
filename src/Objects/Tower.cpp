#include "Tower.h"
#include "Playfield.h"
#include "Enemy.h"

#define RAD(x) x * 3.14159f / 180.0f

Tower::Tower(Playfield* playfield, glm::vec3 pos)
	: playfield(playfield)
{
	model.Load("res/models/tower2.obj");
	this->pos = pos;
	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

Tower::~Tower()
{

}

void Tower::Update()
{
	target = GetTarget();
	if (target != nullptr)
	{
		Rotate(target->pos);
	}
}

Enemy* Tower::GetTarget()
{
	return playfield->GetEnemy(0);
}

void Tower::Rotate(glm::vec3& posTarget)
{
	glm::vec3 dir = glm::normalize(posTarget - pos);
	float angle;

	if (dir.x > 0)
	{
		angle = atan(dir.y / dir.x);
	}
	else if (dir.x < 0)
	{
		angle = atan(dir.y / dir.x) + RAD(180.0f);
	}
	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}