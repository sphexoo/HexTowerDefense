#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
public:
	Enemy(int x, int y);
	~Enemy();
	void Update() override;
	void Move();
};