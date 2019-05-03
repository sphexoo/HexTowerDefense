#include <GL/glew.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexAttributes.h"
#include "Renderer.h"

#define RAD(x) x * 3.14159f / 180.0f

Renderer::Renderer(float fFov, float fWidth, float fHeight, float fZnear, float fZfar)
	:fFov(fFov), fWidth(fWidth), fHeight(fHeight), fZnear(fZnear), fZfar(fZfar)
{
	/* initialize projection matrices */
	projMatrix3D = glm::perspective(RAD(fFov), fWidth / fHeight, fZnear, fZfar);
	projMatrix2D = glm::ortho(0.0f, fWidth, 0.0f, fHeight, -0.5f, 0.5f);
	MVP = glm::mat4(1.0f);

	/* initial OpenGl settings */
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::Clear()
{
	/* Clear color buffer with specified color */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw3D(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix)
{
	/* render 3D object */
	MVP = projMatrix3D * viewMatrix * modelMatrix;
	
	sd.Bind();
	sd.SetUniformMatrix4f("u_MVP", MVP);
	sd.SetUniform1i("u_Texture", 0);

	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw2D(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, Shader& sd, const glm::mat4& modelMatrix)
{
	/* render 2D object */
	MVP = projMatrix2D * modelMatrix;

	sd.Bind();
	sd.SetUniformMatrix4f("u_MVP", MVP);
	sd.SetUniform1i("u_Texture", 0);

	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
