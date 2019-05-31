#pragma once
#include "Entity.h"

class Playfield;

class EnvObj : public Entity
{
private:
	Playfield* playfield;
	float fSpeed = 0.05f;
	int currentTarget = 1;

public:
	EnvObj(Playfield* playfield, glm::vec3 pos);
	~EnvObj();
	void Update() override;
};