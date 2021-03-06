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
	enum Type
	{
		TREE = 0,
		STONE = 1,
		GRASS = 2
	};

public:
	EnvObj(Playfield* playfield, Type type, glm::vec3 pos);
	~EnvObj();
	void Update() override;
};