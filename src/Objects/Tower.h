#pragma once
#include "Entity.h"

class Playfield;

class Tower : public Entity
{
private:
	Playfield* playfield;

public:
	Tower(Playfield* playfield, glm::vec3 pos);
	~Tower();
	void Update() override;
	glm::vec3 GetTarget();
	void Rotate(glm::vec3& posTarget);
};