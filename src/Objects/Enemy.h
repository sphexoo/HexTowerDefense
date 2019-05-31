#pragma once
#include "Entity.h"

class Playfield;

class Enemy : public Entity
{
private:
	Playfield* playfield;
	float fSpeed = 0.01f; 
	int currentTarget = 1;
	float fClock = 0;

public:
	Enemy(Playfield* playfield);
	~Enemy();
	void Update() override;
	void Move();
};