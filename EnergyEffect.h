#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <Windows.h>
#include <gl/GL.h>

#ifndef ENERGYEFFECT
#define ENERGYEFFECT
//Eh, I got lazy. Use this as inheritance for other particle effects ... so much easier. 
class Particle_EnergyEffect : public TextureManager
{
public:
	Particle_EnergyEffect();
	~Particle_EnergyEffect();
	double getX();
	double getY();
	void newEffect(double xPos, double yPos, double secondTimer, double boxRadius, double monsterRotation);
	void drawEffect();
	bool determineToDraw();
	void updateEffect(double timePassed, double xPos, double yPos, double monsterRotation);
	void deleteEffect();
protected:
	double xPos, yPos, boxRadius, Rotation;
	double alphaTransparency;
	bool toDraw;
	double secondsToDeath;
	double totalTime;
};

#endif