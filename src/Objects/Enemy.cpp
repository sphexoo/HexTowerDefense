#include "Enemy.h"
#include "Playfield.h"

Enemy::Enemy(Playfield* playfield)
	: playfield(playfield)
{
	model.LoadPly("res/models/enemy1.ply");
	pos = playfield->GetPath(0)->pos;
	pos_model = pos;

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

	pos_model = pos;
	pos_model.z = 0.3f + 0.3f * sin(fClock);

	fClock += 0.02f;

	modelMatrix = glm::translate(glm::mat4(1.0f), pos_model);

	if (glm::length(playfield->GetPath(currentTarget)->pos - pos) < fSpeed)
	{
		if (playfield->GetPath(currentTarget)->type != Playfield::Tile::TARGET)
		{
			currentTarget++;
		}
		else
		{
			playfield->ClearEnemy(this);
		}
	}
}