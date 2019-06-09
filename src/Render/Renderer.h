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

	Shader* shader_tex;
	Shader* shader_bsc;
	Shader* shader_lgt;
	Shader* shader_dpt;

	/* Shadow mapping */
	Shader* shader_sdw;
	unsigned int depthMapFBO;
	// creating 2d texture
	const unsigned int SHADOW_WIDTH = 1280, SHADOW_HEIGHT = 720;
	unsigned int depthMap;

	// creating light projection matrix
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
	// creating light view matrix (light direction)
	glm::mat4 lightView = glm::lookAt(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// intializing light space matrix
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;


public:
	Renderer(float fFov, float fWidth, float fHeight, float fZnear, float fZfar);
	~Renderer();
	void Clear();
	void Draw3Dscene(const Camera& camera, const Playfield& playfield);
	void Draw3Dbasic(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix);
	void Draw3Dlight(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix);
	void Draw3Dtexture(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix, const Texture& texture, float fColorScale = 1.0f);
	void Draw2Dbasic(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& modelMatrix, const glm::vec4& color);
	void Draw2Dtexture(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& modelMatrix, const Texture& texture, float fColorScale = 1.0f);
	
};