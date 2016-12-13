#include "TimedExplosive.h"
#include <iostream>
#define AREAMULT 4
TimedExplosive::TimedExplosive(std::string Filename, std::string Filename2)
{
	Timer = 0;
	toDraw = false;
	objPosition.xPos = objPosition.yPos = objPosition.boxRadius = 0;
	this->loadTexture(Filename);
	animationTexture[0] = this->getTexture();
	this->deleteTexture();
	this->loadTexture(Filename2);
	animationTexture[1] = this->getTexture();
	this->deleteTexture();
	explosionSet = false;
}


TimedExplosive::~TimedExplosive()
{
	Timer = 0;
	toDraw = false;
	objPosition.xPos = objPosition.yPos = objPosition.boxRadius = 0;
	animationTexture[0] = animationTexture[1] = NULL;
}

double TimedExplosive::getX()
{
	return objPosition.xPos;
}

double TimedExplosive::getY()
{
	return objPosition.yPos;
}

bool TimedExplosive::getToDraw()
{
	return toDraw;
}

void TimedExplosive::newTimedExplosive(double xPos, double yPos, double Timer)
{
	toDraw = true;
	explosionSet = false;
	this->Timer = Timer;
	objPosition.xPos = xPos;
	objPosition.yPos = yPos;
	objPosition.boxRadius = 0.15;
	animationTimer = 0;
	setToClippingPlane();
}

bool TimedExplosive::determineToDraw(double timePassed)
{
	if(toDraw)
	{
		Timer -= timePassed;
		animationTimer += timePassed;
		if(Timer <= 0)
		{
			toDraw = false;
			explosionSet = true;
			return false;
		}
		else
			return true;
	}
	return false;
}

void TimedExplosive::drawExplosive()
{
	if(toDraw)
	{
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		if(animationTimer < Timer)
		{
			glBindTexture(GL_TEXTURE_2D, animationTexture[0]);
			animationTimer += 0.25;
		}
		else if(animationTimer >= Timer)
		{
			glBindTexture(GL_TEXTURE_2D, animationTexture[1]);
			animationTimer = 0;
		}
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

bool TimedExplosive::explosionOff(double objX, double objY, double objBox)
{
	if(explosionSet)
	{
		if(objX - objBox >= objPosition.xPos - objPosition.boxRadius*AREAMULT && objX + objBox <= objPosition.xPos + objPosition.boxRadius*AREAMULT && objY - objBox >= objPosition.yPos - objPosition.boxRadius*AREAMULT && objY + objBox <= objPosition.yPos + objPosition.boxRadius*AREAMULT)
		{
			return true;
		}
		return false;
	}
	return false;
}

double TimedExplosive::getBox()
{
	return objPosition.boxRadius;
}

void TimedExplosive::setToClippingPlane()
{
	double closestX = 0, closestY = 0;
	double newX, newY;
	for(double x = 0.2; x <= 10; x += 0.2)
	{
		for(double y = 0.25; y <= 12.75; y += 0.25)
		{
			newX = x;
			newY = y;
			double square, square2;
			square = pow(newX - objPosition.xPos, 2) + pow(newY - objPosition.yPos, 2);
			square2 = pow(closestX - objPosition.xPos, 2) + pow(closestY - objPosition.yPos, 2);
			square = sqrt(square);
			square2 = sqrt(square2);
			if(square < square2)
			{
				closestX = x;
				closestY = y;
			}
		}
	}
	objPosition.xPos = closestX;
	objPosition.yPos = closestY;
}