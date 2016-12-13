#include "Grenade.h"

Grenade::Grenade(void)
{
	this->loadTexture("Grenade.png");
	exploded = toDraw = false;
	objPosition = NULL;
	xVelocity = yVelocity = explosionTimer = 0;
}

Grenade::Grenade(std::string Filename)
{
	this->loadTexture(Filename);
	exploded = toDraw = false;
	objPosition = NULL;
	xVelocity = yVelocity = explosionTimer = 0;
}

Grenade::~Grenade(void)
{
	objPosition = NULL;
	xVelocity = yVelocity = explosionTimer = 0;
	exploded = toDraw = false;
}

void Grenade::newGrenade(double xPos, double yPos, double pRotation)
{
	objPosition.xPos = xPos;
	objPosition.yPos = yPos;
	toDraw = true;
	explosionTimer = 6;
	xVelocity = (cos(pRotation*PI/180))/100;
	yVelocity = (sin(pRotation*PI/180))/100;
}

void Grenade::newGrenade(vec2 objPosition, double pRotation)
{
	this->objPosition = objPosition;
	toDraw = true;
	explosionTimer = 6;
	xVelocity = (cos(pRotation*PI/180))/100;
	yVelocity = (sin(pRotation*PI/180))/100;
}

void Grenade::updateGrenade(double Timer)
{
	objPosition.xPos += xVelocity;
	objPosition.yPos += yVelocity;
	explosionTimer -= Timer;
	if(explosionTimer < 0)
	{
		explodeGrenade();
	}
}

void Grenade::explodeGrenade()
{
	toDraw = false;
	exploded = true;
	explosionTimer = 0;
	xVelocity = yVelocity = 0;
}