#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <gl/GL.h>
#include "TextureManager.h"
#include "vec2.h"

class TimedExplosive : public TextureManager
{
public:
	TimedExplosive(std::string Filename, std::string Filename2);
	~TimedExplosive();
	void newTimedExplosive(double xPos, double yPos, double Timer);
	bool determineToDraw(double timePassed);
	double getX();
	double getY();
	bool getToDraw();
	void deleteExplosive();
	bool explosionOff(double objX, double objY, double objBox);
	void drawExplosive();
	bool explosionSet;
	double getBox();
protected:
	vec2 objPosition;
	void setToClippingPlane();
private:
	GLuint animationTexture[2];
	double Timer;
	double animationTimer;
	bool toDraw;
};

