#include <SFML/Graphics.hpp>
#include "Monster.h"
#include "TextureManager.h"
#include "vec2.h"
#include <Windows.h>
#include <gl/GL.h>

#pragma once

#define MAXBARRICADE 15

class Barricade : public TextureManager
{
public:
	Barricade(std::string Filename);
	Barricade();
	~Barricade();
	void newBarricade(double xPos, double yPos, int armor, double Rotation);
	bool interactedBarricade(unsigned int itemID);
	void removeBarricade();
	void drawBarricade();
	bool determineToDraw();
	double getX();
	double getY();
	unsigned int getHealth();
	unsigned int *getHealthP();
	double getBoxRadius();
protected:
	vec2 objPosition;
private:
	unsigned int health;
	int armor;
	bool toDraw;
	double Rotation;
};