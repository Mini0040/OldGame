#include "TextureManager.h"
#include <iostream>
GLuint TextureManager::getTexture()
{
	return Texture;
}

void TextureManager::setTexture(GLuint Texture)
{
	this->Texture = Texture;
}

bool TextureManager::loadTexture(std::string Filename)
{
	sf::Image Image;
	if(!Image.LoadFromFile(Filename))
	{
		return false;
	}
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image.GetWidth(), Image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	std::cout << Filename << " loaded" << std::endl;
	return true;
}

bool TextureManager::deleteTexture()
{
	Texture = NULL;
	return true;
}

