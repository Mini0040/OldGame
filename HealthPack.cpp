#include "HealthPack.h"


HealthPack::HealthPack(void)
{
	this->loadTexture("HealthPack.png");
	objPosition.xPos = objPosition.yPos = objPosition.boxRadius = 0;
	amountHealed = 0;
	toDraw = false;
}

HealthPack::HealthPack(std::string Filename)
{
	this->loadTexture(Filename);
	objPosition.xPos = objPosition.yPos = objPosition.boxRadius = 0;
	amountHealed = 0;
	toDraw = false;
}

HealthPack::~HealthPack(void)
{
	this->deleteTexture();
	objPosition = NULL; 
	amountHealed = 0;
	toDraw = false;
}

double HealthPack::getX()
{
	return objPosition.xPos;
}

double HealthPack::getY()
{
	return objPosition.yPos;
}

void HealthPack::interactedHealthPack(unsigned int *pHealth, const unsigned int maxHP)
{
	if(toDraw)
	{
		if(*pHealth < maxHP)
		{
			if(*pHealth + amountHealed > maxHP)
			{
				*pHealth = maxHP;
			}
			else
			{
				*pHealth += amountHealed;
			}
			removeHealthPack();
		}
	}
}

bool HealthPack::newHealthPack(double xPos, double yPos, double boxRadius, int amountHealed)
{
	objPosition.xPos = xPos;
	objPosition.yPos = yPos;
	this->amountHealed = amountHealed;
	objPosition.boxRadius = boxRadius;
	toDraw = true;
	return true;
}

bool HealthPack::newHealthPack(vec2 objPosition, int amountHealed)
{
	this->objPosition = objPosition;
	this->amountHealed = amountHealed;
}

void HealthPack::removeHealthPack()
{
	toDraw = false;
	amountHealed = 0;
}

void HealthPack::drawHealthPack(double TimePassed)
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture());
	glColor4f(1, 1, 1, 1);
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

bool HealthPack::getToDraw()
{
	return toDraw;
}

double HealthPack::getBox()
{
	return objPosition.boxRadius;
}