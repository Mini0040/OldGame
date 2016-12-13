#pragma once

#include "TextureManager.h"
#include "vec2.h"
#include <SFML/Graphics.hpp>

class Grenade : public TextureManager
{
public:
	Grenade(void);
	Grenade(std::string Filename);
	~Grenade(void);
	void newGrenade(double xPos, double yPos, double pRotation);
	void newGrenade(vec2 objPosition, double pRotation);
	void explodeGrenade();
	void updateGrenade(double Timer);
	double getX();
	double getY();
protected:
	vec2 objPosition;
private:
	double xVelocity, yVelocity;
	bool exploded, toDraw;
	double explosionTimer;
};

