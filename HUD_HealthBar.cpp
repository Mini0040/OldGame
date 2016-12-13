#include "HUD_HealthBar.h"
#include <iostream>

HealthBar::HealthBar(std::string Filename)
{
	this->loadTexture(Filename);
	objHealth = 0;
	maxObjHealth = 100;
	Position.xPos = Position.yPos = 0;
}

HealthBar::HealthBar()
{
	objHealth = 0;
	maxObjHealth = 100;
	Position.xPos = Position.yPos = 0;
}

HealthBar::~HealthBar()
{
	this->deleteTexture();
	objHealth = maxObjHealth = Position.xPos = Position.yPos = 0;
}

void HealthBar::newHealthBar(double xPos, double yPos, double objHealth, double maxObjHealth)
{
	Position.xPos = xPos;
	Position.yPos = yPos;
	this->objHealth = objHealth;
	this->maxObjHealth = maxObjHealth;
}

void HealthBar::updateHealthBar(double objHealth)
{
	this->objHealth = objHealth;
}

void HealthBar::drawHealthBar()
{
	glPushMatrix();
	glColor3f((maxObjHealth - objHealth)/maxObjHealth, (objHealth/maxObjHealth), 0);
	glBegin(GL_QUADS);
		glVertex3f(Position.xPos, Position.yPos - 10, 0);
		glVertex3f(Position.xPos, Position.yPos + 10, 0);
		glVertex3f(Position.xPos + ((objHealth/maxObjHealth)*100), Position.yPos + 10, 0);
		glVertex3f(Position.xPos + ((objHealth/maxObjHealth)*100), Position.yPos - 10, 0);
	glEnd();
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void HealthBar::drawHealthBar(double boxRadius)
{
	glPushMatrix();
	glColor3f((maxObjHealth - objHealth)/maxObjHealth, (objHealth/maxObjHealth), 0);
	glBegin(GL_QUADS);
		glVertex3f(Position.xPos, Position.yPos - 0.01, 0);
		glVertex3f(Position.xPos, Position.yPos + 0.01, 0);
		glVertex3f(Position.xPos + ((objHealth/maxObjHealth)*boxRadius), Position.yPos + 0.01, 0);
		glVertex3f(Position.xPos + ((objHealth/maxObjHealth)*boxRadius), Position.yPos - 0.01, 0);
	glEnd();
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void HealthBar::updateHealthBar(double xPos, double yPos, double objHealth)
{
	Position.xPos = xPos;
	Position.yPos = yPos;
	this->objHealth = objHealth;
}
