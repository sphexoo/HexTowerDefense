#include "Enemy.h"

Enemy::Enemy(glm::vec3 pos)
{
	model.Load("res/models/tower1.obj");
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

}