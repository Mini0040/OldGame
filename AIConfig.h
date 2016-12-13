#include <SFML/Graphics.hpp>
#include <math.h>
#include "CollisionManager.h"

#ifndef AICONF
#define AICONF

class AIConfig
{
public:
	AIConfig();
	~AIConfig();
	bool shiftRotation(double pX, double pY, double xPos, double yPos, double *Rotation);
	void moveNPC(double *xPos, double *yPos, double Rotation, double movementMult);
	bool attackPlayer(double xPos, double yPos, double objX, double objY, unsigned int *objHP, double objBox, double damageOutput);
	bool attackObject(double xPos, double yPos, double objX, double objY, unsigned int *objHP, double objBox, double damageOutput);
	bool allowMove;
	double allowTimer;
	const double resetAllowTimer;
protected:
	CollisionManager collision;
};

#endif