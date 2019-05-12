#include "Enemy.h"

Enemy::Enemy(int x, int y)
{
	model.Load("res/models/tower1.obj");
	modelMatrix = glm::mat4(1.0f);
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