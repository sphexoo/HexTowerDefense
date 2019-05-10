#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Shader;
class VertexBuffer;
class IndexBuffer;
class VertexAttributes;
class Texture;

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

public:
	Renderer(float fFov, float fWidth, float fHeight, float fZnear, float fZfar);
	void Clear();
	void Draw3Dbasic(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix, const glm::vec4& color);
	void Draw3Dlight(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix, const glm::vec4& color);
	void Draw3Dtexture(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix, const Texture& texture);
	void Draw2Dbasic(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& modelMatrix, const glm::vec4& color);
	void Draw2Dtexture(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& modelMatrix, const Texture& texture);
};