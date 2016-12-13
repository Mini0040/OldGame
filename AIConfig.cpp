#include "AIConfig.h"
#include <iostream>
#define PI 3.141592654
#define MULT 2.025
#define OBJMULT 1.75
AIConfig::AIConfig() : resetAllowTimer(1.5)
{
	allowTimer = 0;
	allowMove = true;
};

AIConfig::~AIConfig()
{
	allowMove = false;
};

bool AIConfig::shiftRotation(double pX, double pY, double xPos, double yPos, double *Rotation)
{
	double square = pow(pX - xPos, 2) + pow(pY - yPos, 2);
	square = sqrt(square);
	if(square <= 1.65)
	{
		double radian = atan2(pY - yPos, pX - xPos);
		*Rotation = (radian*180/PI);
		return true;
	}
	return false;
}

void AIConfig::moveNPC(double *xPos, double *yPos, double Rotation, double movementMult)
{
	if(allowMove)
	{
		*xPos += (cos(Rotation*PI/180))/movementMult;
		*yPos += (sin(Rotation*PI/180))/movementMult;
	}
}

bool AIConfig::attackPlayer(double xPos, double yPos, double objX, double objY, unsigned int *objHP, double objBox, double damageOutput)
{
	if(collision.totalCollision(xPos + 0.125, objX + (objBox/2), yPos + 0.125, objY + (objBox/2), 0.0000625, objBox))
	{
		if(*objHP - damageOutput < 0)
		{
			*objHP = 0;
			return true;
		}
		*objHP -= damageOutput;
		allowMove = false;
		allowTimer = resetAllowTimer;
		return true;
	}
	return false;
}

bool AIConfig::attackObject(double xPos, double yPos, double objX, double objY, unsigned int *objHP, double objBox, double damageOutput)
{
	/*if(xPos >= objX - objBox*OBJMULT && xPos + 0.125*MULT <= objX + objBox*OBJMULT && yPos >= objY - objBox*OBJMULT && yPos + 0.125*MULT <= objY + objBox*OBJMULT)
	{
		if(*objHP - damageOutput < 0)
		{
			return true;
		}
		*objHP -= damageOutput;
		allowMove = false;
		allowTimer = resetAllowTimer;
		return true;
	}
	return false;*/
	if(collision.totalCollision(xPos, objX, yPos, objY, 0.00625, objBox))
	{
		if(*objHP - damageOutput < 0)
		{
			*objHP = 0;
			return true;
		}
		*objHP -= damageOutput;
		allowMove = false;
		allowTimer = resetAllowTimer;
		return true;
	}
	return false;
}