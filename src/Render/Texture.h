#pragma once
#include <string>

class Texture
{
private:
	unsigned int ID;
	std::string frompath;
	unsigned char* LocalBuffer;
	int width, height, bpp; // bits per pixel

public: 
	Texture(const std::string& frompath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	int GetWidth() { return width; }
	int GetHeight() { return height; }
};