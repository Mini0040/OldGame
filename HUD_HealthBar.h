#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "vec2.h"

class HealthBar : public TextureManager
{
public:
	HealthBar();
	HealthBar(std::string Filename);
	~HealthBar();
	void drawHealthBar();
	void drawHealthBar(double boxRadius);
	void newHealthBar(double xPos, double yPos, double objHealth, double maxObjHealth);
	void updateHealthBar(double objHealth);
	void updateHealthBar(double xPos, double yPos, double objHealth);
protected:
	vec2 Position;
private:
	double objHealth, maxObjHealth;
};