#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
	float fSpeed = 1.0f; 

public:
	Enemy(glm::vec3 pos);
	~Enemy();
	void Update() override;
	void Move();
};