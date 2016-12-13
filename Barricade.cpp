#include "Barricade.h"
#include <iostream>

Barricade::Barricade(std::string Filename)
{
	objPosition.xPos = objPosition.yPos = objPosition.boxRadius = 0;
	toDraw = false;
	health = armor = 0;
	this->loadTexture(Filename);
}

Barricade::Barricade()
{
	objPosition.xPos = objPosition.yPos = objPosition.boxRadius = 0;
	toDraw = false;
	health = armor = 0;
	this->loadTexture("Barricade.png");
}

Barricade::~Barricade()
{
	objPosition.xPos = objPosition.yPos = objPosition.boxRadius = 0;
	toDraw = false;
	health = armor = 0;
	this->deleteTexture();
}

void Barricade::newBarricade(double xPos, double yPos, int armor, double Rotation)
{
	objPosition.xPos = xPos;
	objPosition.yPos = yPos;
	this->armor = armor;
	health = 100;
	objPosition.boxRadius = 0.1;
	toDraw = true;
	this->Rotation = Rotation;
}

bool Barricade::interactedBarricade(unsigned int itemID)
{
	if(toDraw)
	{
		switch(itemID)
		{
		case 200:
			if(health - (1 - armor) <= 5)
			{
				health = 5;
				return true;
				break;
			}
			health = health - (1 - armor);
			return true;
			break;
		default:
			return false;
		}
	}
	return false;
}

void Barricade::removeBarricade()
{
	health = armor = 0;
	objPosition.xPos = objPosition.yPos = objPosition.boxRadius = 0;
	toDraw = false;
}

bool Barricade::determineToDraw()
{
	if(health > 5)
	{
		toDraw = true;
		return true;
	}
	toDraw = false;
	return false;
}

double Barricade::getX()
{
	return objPosition.xPos;
}

double Barricade::getY()
{
	return objPosition.yPos;
}

unsigned int Barricade::getHealth()
{
	return health;
}

double Barricade::getBoxRadius()
{
	return objPosition.boxRadius;
}

void Barricade::drawBarricade()
{
	if(determineToDraw())
	{
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->getTexture());
		glTranslatef(objPosition.xPos, objPosition.yPos, 0);
		glRotatef(Rotation, 0, 0, 1);
		glTranslatef(-objPosition.xPos, -objPosition.yPos, 0);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 0); glVertex3f(objPosition.xPos - objPosition.boxRadius, objPosition.yPos - objPosition.boxRadius, 0);
			glTexCoord2d(0, 1); glVertex3f(objPosition.xPos - objPosition.boxRadius, objPosition.yPos + objPosition.boxRadius, 0);
			glTexCoord2d(1, 1); glVertex3f(objPosition.xPos + objPosition.boxRadius, objPosition.yPos + objPosition.boxRadius, 0);
			glTexCoord2d(1, 0); glVertex3f(objPosition.xPos + objPosition.boxRadius, objPosition.yPos - objPosition.boxRadius, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}

unsigned int* Barricade::getHealthP()
{
	return &health;
}