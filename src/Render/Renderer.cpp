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

#include "Playfield.h"
#include "Camera.h"
#include "Tower.h"
#include "Enemy.h"
#include "EnvObj.h"

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
	shader_texture = new Shader("res/shaders/texture_vertex.shader", "res/shaders/texture_fragment.shader");
	shader_shadow = new Shader("res/shaders/shadow_light_vertex.shader", "res/shaders/shadow_light_fragment.shader");
	shader_depth = new Shader("res/shaders/depth_vertex.shader", "res/shaders/depth_fragment.shader");

	/* initial OpenGl settings */
	glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glPointSize(5);

	/* Shadow mapping */
	// creating frame buffer 
	glGenFramebuffers(1, &depthMapFBO);

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, (unsigned int)fWidth, (unsigned int)fHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// attach depth buffer to frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glActiveTexture(GL_TEXTURE0);

	shader_shadow->Bind();
	shader_shadow->SetUniform1i("shadowMap", 1);
}

Renderer::~Renderer()
{
	delete shader_texture;
	delete shader_shadow;
	delete shader_depth;
}

void Renderer::Clear()
{
	/* Clear color buffer with specified color */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw3Dscene(Camera& camera, Playfield& playfield)
{
	/* Generate depth map */
	glCullFace(GL_FRONT);

	shader_depth->Bind();
	shader_depth->SetUniformMatrix4f("u_lightSpaceMatrix", lightSpaceMatrix);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	playfield.model.DrawDepth(*this, camera.viewMatrix, playfield.modelMatrix);

	for (unsigned int i = 0; i < playfield.towers.size(); i++)
	{
		playfield.towers[i]->DrawDepth(*this, camera.viewMatrix);
	}

	for (unsigned int i = 0; i < playfield.enemies.size(); i++)
	{
		playfield.enemies[i]->DrawDepth(*this, camera.viewMatrix);
	}

	for (unsigned int i = 0; i < playfield.envobjects.size(); i++)
	{
		playfield.envobjects[i]->DrawDepth(*this, camera.viewMatrix);
	}
	glCullFace(GL_BACK);

	/* Draw scene */
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	Clear();
	shader_shadow->Bind();
	shader_shadow->SetUniformMatrix4f("lightSpaceMatrix", lightSpaceMatrix);
	shader_shadow->SetUniform3f("lightPos", lightPos);
	shader_shadow->SetUniform3f("viewPos", camera.lookFrom);
	shader_shadow->SetUniformMatrix4f("projection", projMatrix3D);
	shader_shadow->SetUniformMatrix4f("view", camera.viewMatrix);
	
	//shader_shadow->SetUniformMatrix4f("model", playfield.modelMatrix);
	playfield.Draw(*this, camera.viewMatrix);

	
	for (unsigned int i = 0; i < playfield.towers.size(); i++)
	{
		playfield.towers[i]->Draw(*this, camera.viewMatrix);
	}

	for (unsigned int i = 0; i < playfield.enemies.size(); i++)
	{
		playfield.enemies[i]->Draw(*this, camera.viewMatrix);
	}

	for (unsigned int i = 0; i < playfield.envobjects.size(); i++)
	{
		playfield.envobjects[i]->Draw(*this, camera.viewMatrix);
	}
}


void Renderer::Draw3Dobject(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix)
{
	/* render 3D object */
	//MVP = projMatrix3D * viewMatrix * modelMatrix;

	shader_shadow->Bind();
	shader_shadow->SetUniformMatrix4f("model", modelMatrix);

	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw3Ddepth(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix)
{
	/* render 3D object */
	MVP = projMatrix3D * viewMatrix * modelMatrix;

	shader_depth->Bind();
	shader_depth->SetUniformMatrix4f("u_model", modelMatrix);

	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw2Dtexture(const VertexBuffer& vb, const VertexAttributes& va, const IndexBuffer& ib, const glm::mat4& modelMatrix, const Texture& texture, float fColorScale /* = 0.0f */)
{
	/* render 2D object */
	MVP = projMatrix2D * modelMatrix;

	shader_texture->Bind();
	texture.Bind();

	shader_texture->SetUniform1i("u_Texture", 0);
	shader_texture->SetUniformMatrix4f("u_MVP", MVP);
	shader_texture->SetUniform1f("u_ColorScale", fColorScale);
	
	vb.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}