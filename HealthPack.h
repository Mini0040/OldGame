#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "vec2.h"
#include "GlowEffect.h"

#define MAXDROP 20

class HealthPack : public TextureManager
{
public:
	HealthPack(void);
	HealthPack(std::string Filename);
	~HealthPack(void);
	bool newHealthPack(double xPos, double yPos, double boxRadius, int amountHealed);
	bool newHealthPack(vec2 objPosition, int amountHealed);
	void removeHealthPack();
	void drawHealthPack(double TimePassed);
	void interactedHealthPack(unsigned int* pHealth, const unsigned int maxHP);
	double getX();
	double getY();
	bool getToDraw();
	double getBox();
	Particle_GlowEffect GlowEffect;
protected:
	vec2 objPosition;
private:
	int amountHealed;
	bool toDraw;
};