#include "ExplosionEffect.h"
#include <cstdlib>
#include <time.h>

Particle_ExplosionEffect::Particle_ExplosionEffect()
{
	xPos = yPos = alphaTransparency = 0;
	toDraw = false;
	secondsToDeath = 0;
}

Particle_ExplosionEffect::~Particle_ExplosionEffect()
{
	xPos = yPos = alphaTransparency = 0;
	toDraw = false;
	secondsToDeath = 0;
	this->deleteTexture();
}

void Particle_ExplosionEffect::randomizeExplosions(double xPos, double yPos)
{
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);
	double xhigh = xPos + (boxRadius/2);
	double xlow = xPos - (boxRadius/2);
	double yHigh = yPos + (boxRadius/2);
	double yLow = yPos - (boxRadius/2);
	this->xPos = sf::Randomizer::Random((float)xlow, xhigh);
	this->yPos = sf::Randomizer::Random((float)yLow, yHigh);
}

void Particle_ExplosionEffect::updateEffect(double timePassed)
{
	secondsToDeath -= timePassed;
	alphaTransparency = secondsToDeath/totalTime;
}