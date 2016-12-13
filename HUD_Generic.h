#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "vec2.h"

class GenericHUD : public TextureManager
{
public:
	GenericHUD();
	GenericHUD(std::string Filename);
	~GenericHUD();
	void drawHUD();
	void newHUD(double xPos, double yPos, double xRad, double yRad);
	double getX();
	double getY();
protected:
	vec2 objPosition;
private:
	double xRad, yRad;
};