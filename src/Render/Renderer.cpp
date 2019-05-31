#include <GL/glew.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexAttributes.h"
#include "Texture.h"
#include "Renderer.h"
#include "Input.h"

#define RAD(x) x * 3.14159f / 180.0f

extern Input input;

Renderer::Renderer(float fFov, float fWidth, float fHeight, float fZnear, float fZfar)
	:fFov(fFov), fWidth(fWidth), fHeight(fHeight), fZnear(fZnear), fZfar(fZfar)
{
	/* initialize projection matrices */
	projMatrix3D = glm::perspective(RAD(fFov), fWidth / fHeight, fZnear, fZfar);
	projMatrix2D = glm::ortho(0.0f, fWidth, 0.0f, fHeight, -0.5f, 0.5f);
	MVP = glm::mat4(1.0f);

	/* create Shaders */
	shader_tex = new Shader("res/shaders/texture_vertex.shader", "res/shaders/texture_fragment.shader");
	shader_bsc = new Shader("res/shaders/basic_vertex.shader", "res/shaders/basic_fragment.shader");
	shader_lgt = new Shader("res/shaders/light_vertex.shader", "res/shaders/light_fragment.shader");

	/* initial OpenGl settings */
	glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glPointSize(5);
}

Renderer::~Renderer()
{
	delete shader_tex;
	delete shader_bsc;
	delete shader_lgt;
}

void Renderer::Clear()
{
	/* Clear color buffer with specified color */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw3Dbasic(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix)
{
	/* render 3D object */
	MVP = projMatrix3D * viewMatrix * modelMatrix;
	
	sd.Bind();

	sd.SetUniformMatrix4f("u_MVP", MVP);

	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw3Dlight(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix)
{
	/* render 3D object */
	MVP = projMatrix3D * viewMatrix * modelMatrix;

	sd.Bind();

	sd.SetUniformMatrix4f("u_MVP", MVP);

	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw3Dtexture(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix, const Texture& texture, float fColorScale /* = 0.0f */)
{
	/* render 3D object */
	MVP = projMatrix3D * viewMatrix * modelMatrix;

	sd.Bind();
	texture.Bind();

	sd.SetUniformMatrix4f("u_MVP", MVP);
	sd.SetUniform1i("u_Texture", 0);
	sd.SetUniform1f("u_ColorScale", fColorScale);

	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw2Dbasic(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& modelMatrix, const glm::vec4& color)
{
	/* render 2D object */
	MVP = projMatrix2D * modelMatrix;

	sd.Bind();

	sd.SetUniform4f("u_Color", color.x, color.y, color.z, color.w);
	sd.SetUniformMatrix4f("u_MVP", MVP);

	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw2Dtexture(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& modelMatrix, const Texture& texture, float fColorScale /* = 0.0f */)
{
	/* render 2D object */
	MVP = projMatrix2D * modelMatrix;

	sd.Bind();
	texture.Bind();

	sd.SetUniform1i("u_Texture", 0);
	sd.SetUniformMatrix4f("u_MVP", MVP);
	sd.SetUniform1f("u_ColorScale", fColorScale);
	
	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}