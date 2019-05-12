#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::Draw(Renderer& renderer, Shader& shader, glm::mat4& viewMatrix)
{
	model.Draw(renderer, shader, viewMatrix, modelMatrix);
}
