#include "Player.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "AIConfig.h"
#include "HUD_HealthBar.h"
#include "HealthPack.h"
#include <Windows.h>
#include <gl/GL.h>

#pragma once

class Monster
{
public:
	void renderMonster(double xPos, double yPos, double timePassed);
	bool interactedMonster(double xPos, double yPos, unsigned int itemID, double Rotation);
	void interactedMonster(unsigned int itemID);
	Monster();
	~Monster();
	int getHealth();
	bool toDraw;
	bool loadTexture(std::string Filename);
	void setMonsterPosition(double xPos, double yPos);
	bool determineToDraw();
	void setTexture(GLuint Texture);
	GLuint getTexture();
	double getX();
	double getY();
	double getRotation();
	AIConfig aConf;
	double getDamage();
	double movementMult;
	double getAttackTime();
	void setAttackTime(double PassTime);
	HealthBar healthBar;
	HealthPack hPack;
	void reviveMonster(double xPos, double yPos);
protected:
	bool loadMonsterPositions(std::string Filename);
	bool loadMonsterType(std::string Filename);
	bool loadConfig();
	void saveToConfig();
	void savePositions(std::string Filename);
	void saveType(std::string Filename);
	double xPos, yPos;
	int health;
	double damageOutput;
	double Rotation;
	GLuint Texture;
	double attackTimer;
};