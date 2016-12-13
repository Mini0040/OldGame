#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <gl/GL.h>

#ifndef TEXTURE_MANG
#define TEXTURE_MANG

class TextureManager
{
public:
	GLuint getTexture();
	bool loadTexture(std::string Filename);
	void setTexture(GLuint Texture);
	bool deleteTexture();
private:
	GLuint Texture;
};

#endif