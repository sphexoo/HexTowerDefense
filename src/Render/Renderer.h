#pragma once

class Shader;
class VertexBuffer;
class IndexBuffer;
class VertexAttributes;

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
	void Draw3D(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix);
	void Draw2D(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& modelMatrix);
};