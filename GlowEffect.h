#pragma once

#include <SFML/Graphics.hpp>
#include "vec2.h"
#include "TextureManager.h"
#include <Windows.h>
#include <gl/GL.h>

class Particle_GlowEffect : public TextureManager
{
public:
	Particle_GlowEffect();
	Particle_GlowEffect(std::string Filename);
	~Particle_GlowEffect();
	void updateEffect(double timePassed);
	void drawEffect(double timePassed);
	void newEffect(double xPos, double yPos, double boxRadius);
	void newEffect(vec2);
	double getX();
	double getY();
	void removeEffect();
protected:
	vec2 objPosition;
	double alphaValue;
	bool toDraw;
	bool amp;
};