#include "Enemy.h"
#include "Playfield.h"

Enemy::Enemy(Playfield* playfield)
	: playfield(playfield)
{
	model.Load("res/models/tower1.obj");
	pos = playfield->GetPath(0)->pos;
	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	Move();
}

void Enemy::Move()
{
	glm::vec3 dir = playfield->GetPath(currentTarget)->pos - pos;
	pos += glm::normalize(dir) * fSpeed;

	modelMatrix = glm::translate(glm::mat4(1.0f), pos);

	if (glm::length(playfield->GetPath(currentTarget)->pos - pos) < 0.01f && playfield->GetPath(currentTarget)->type != Playfield::Tile::TARGET)
	{
		currentTarget++;
	}
}