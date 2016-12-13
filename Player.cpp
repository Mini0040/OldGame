#include "Player.h"
#include <iostream>
#include <math.h>
#include "ResourceHeaders.h"

#define PI 3.141592654

Player::Player() : zPos(0)
{
	xPos = 0.0;
	yPos = 0.0;
	Rotation = 0.0;
	heldItem = 3;
	for(int i = 0; i < 20; i++)
	{
		inventory[i] = 0;
	}
	surfaceArea = 0.0;
	availAmmo = 45;
	reserveAmmo = 45;
	maxClip = 45;
	health = 100;
}

Player::~Player()
{
	xPos = 0.0;
	yPos = 0.0;
	Texture = NULL;
	surfaceArea = 0;
	heldItem = 0;
	for(int i = 0; i < 20; i++)
	{
		inventory[i] = 0;
	}
	Rotation = 0.0;
}

unsigned int Player::getHealth()
{
	return health;
}

unsigned int Player::getHeldItem()
{
	return heldItem;
}

double Player::getRotation()
{
	return Rotation;
}

double Player::getX()
{
	return xPos;
}

double Player::getY()
{
	return yPos;
}

bool Player::loadPlayerTexture(std::string Filename)
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
	std::cout << "Player Texture Loaded" << std::endl;
	return true;
}

void Player::renderPlayer()
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(xPos + 0.125, yPos + 0.125, 0);
	glRotatef(Rotation, 0.0, 0.0, 1.0);
	glTranslatef(-xPos - 0.125, -yPos - 0.125, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->Texture);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0); glVertex2f(xPos, yPos);
		glTexCoord2d(1.0, 0.0); glVertex2f(xPos + 0.25, yPos);
		glTexCoord2d(1.0, 1.0); glVertex2f(xPos + 0.25, yPos + 0.25);
		glTexCoord2d(0.0, 1.0); glVertex2f(xPos, yPos + 0.25);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void Player::setPlayerPosition(double xPos, double yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
}

void Player::figureOutRotation(double mouseX, double mouseY)
{
	double radian = atan2(mouseX - 440, mouseY - 265);
	Rotation = radian*180/PI;
	Rotation -= 90;
};

void Player::setHeldItem(unsigned int ItemHeld)
{
	heldItem = ItemHeld;
}

unsigned int* Player::getHealth(bool YouNeed)
{
	return &health;
}

void Player::setHealth(unsigned int heelth)
{
	health = heelth;
}