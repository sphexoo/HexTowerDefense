#pragma once
#include "Entity.h"

class Playfield;
class Enemy;

class Tower : public Entity
{
private:
	Playfield* playfield;
	Enemy* target = nullptr;

public:
	Tower(Playfield* playfield, glm::vec3 pos);
	~Tower();
	void Update() override;
	Enemy* GetTarget();
	void Rotate(glm::vec3& posTarget);
};