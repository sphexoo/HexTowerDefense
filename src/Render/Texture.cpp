#include <GL/glew.h>

#include "Logger.h"
#include "Texture.h"
#include "stb_image.h"

/* Access the logger object globally created in Application.cpp */
extern Logger logger;


Texture::Texture(const std::string& frompath)
{
	ID = 0; 
	this->frompath = frompath;
	LocalBuffer = nullptr;
	width = 0;
	height = 0;
	bpp = 0;

	stbi_set_flip_vertically_on_load(1);
	LocalBuffer = stbi_load(frompath.c_str(), &width, &height, &bpp, 4);

	if (!LocalBuffer)
	{
		logger.log("Texture not loaded. Texture Buffer is empty", Logger::Warning);
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (LocalBuffer)
	{
		stbi_image_free(LocalBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::Bind(unsigned int slot/* = 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
