#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Shader.h"

class Shader;
class VertexBuffer;
class IndexBuffer;
class VertexAttributes;
class Texture;

class Playfield;
class Camera;

class Renderer
{
private:
	float fFov;
	float fWidth;
	float fHeight;
	float fZnear;
	float fZfar;

public: 
	glm::mat4 projMatrix3D;
	glm::mat4 projMatrix2D;
	glm::mat4 MVP;

	Shader* shader_texture;
	Shader* shader_depth;
	Shader* shader_shadow;

	/* Shadow mapping */
	unsigned int depthMapFBO;
	// creating 2d texture
	unsigned int depthMap;

	// creating light projection matrix
	glm::mat4 lightProjection = glm::ortho(-10.0f, 12.0f, -5.0f, 25.0f, 1.0f, 50.0f);
	// creating light view matrix (light direction)
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// intializing light space matrix
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;


public:
	Renderer(float fFov, float fWidth, float fHeight, float fZnear, float fZfar);
	~Renderer();
	void Clear();
	void Draw3Dscene(Camera& camera, Playfield& playfield);
	void Draw3Dobject(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix);
	void Draw2Dtexture(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, const glm::mat4& modelMatrix, const Texture& texture, float fColorScale = 1.0f);
	
};