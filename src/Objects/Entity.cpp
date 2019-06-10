#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::Draw(Renderer& renderer, glm::mat4& viewMatrix)
{
	model.Draw(renderer, viewMatrix, modelMatrix);
}

void Entity::DrawDepth(Renderer& renderer, glm::mat4& viewMatrix)
{
	model.DrawDepth(renderer, viewMatrix, modelMatrix);
}
