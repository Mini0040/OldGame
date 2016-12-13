#include "Monster.h"
#include <SFML/Graphics.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>

#define PI 3.14159265

Monster::Monster()
{
	toDraw = true;
	health = 100;
	damageOutput = sf::Randomizer::Random(1, 50);
	attackTimer = 1.25;
	movementMult = sf::Randomizer::Random(50, 300);
	//loadConfig();
};

void Monster::reviveMonster(double xPos, double yPos)
{
	toDraw = true;
	health = 100;
	damageOutput = sf::Randomizer::Random(1, 50);
	attackTimer = 1.25;
	movementMult = sf::Randomizer::Random(50, 300);
	this->xPos = xPos;
	this->yPos = yPos;
}

Monster::~Monster()
{
	//saveToConfig();
}

void Monster::renderMonster(double xPos, double yPos, double timePassed)
{
	if(toDraw)
	{
		if(aConf.shiftRotation(xPos, yPos, this->xPos, this->yPos, &Rotation))
		{
			if(aConf.allowTimer <= 0)
			{
				aConf.allowMove = true;
			}
			aConf.moveNPC(&this->xPos, &this->yPos, Rotation, movementMult);
		}
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(this->xPos + 0.125, this->yPos + 0.125, 0);
	glRotatef(Rotation, 0.0, 0.0, 1.0);
	glTranslatef(-this->xPos - 0.125, -this->yPos - 0.125, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->Texture);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0); glVertex3f(this->xPos, this->yPos, 0);
		glTexCoord2d(0.0, 1.0); glVertex3f(this->xPos, this->yPos + 0.25, 0);
		glTexCoord2d(1.0, 1.0); glVertex3f(this->xPos + 0.25, this->yPos + 0.25, 0);
		glTexCoord2d(1.0, 0.0); glVertex3f(this->xPos + 0.25, this->yPos, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
	healthBar.updateHealthBar(this->xPos, this->yPos + (0.25 + 0.02), this->health);
	healthBar.drawHealthBar(0.25);
	attackTimer -= timePassed;
	aConf.allowTimer -= timePassed;
	}
}

bool Monster::loadTexture(std::string Filename)
{
	sf::Image Image;
	if(!Image.LoadFromFile(Filename))
	{
		return false;
	}
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image.GetWidth(), Image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	std::cout << "Monster Texture Loaded" << std::endl;
	return true;
}

void Monster::setMonsterPosition(double xPos, double yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
	healthBar.newHealthBar(this->xPos, this->yPos + (0.25 + 0.02), this->health, 100);
}

bool Monster::interactedMonster(double xPos, double yPos, unsigned int itemID, double Rotation)
{
	double setAmount = cos(Rotation*PI/180);
	double Multiplier;
	if(setAmount > 0)
		Multiplier = 1;
	else
		Multiplier = -1;
	if(xPos + (0.001*Multiplier) >= this->xPos - 0.25 && xPos + (0.001*Multiplier) <= this->xPos && yPos >= this->yPos - 0.125 && yPos <= this->yPos + 0.125)
	{
		switch(itemID)
		{
		case 0:
			health -= 10;
			break;
		case 1:
			health -= 15;
			break;
		case 2:
			health -= 20;
			break;
		case 3: //bullet
			health -= 12;
			break;
		default:
			health++;
			break;
	    }
		return true;
	}
	return false;
}

bool Monster::determineToDraw()
{
	if(health > 5)
	{
		toDraw = true;
		return true;
	}
	else
	{
		toDraw = false;
		return false;
	}
	std::cout << toDraw << std::endl;
}

int Monster::getHealth()
{
	return health;
}

void Monster::setTexture(GLuint Texture)
{
	this->Texture = Texture;
}

GLuint Monster::getTexture()
{
	return this->Texture;
}

double Monster::getX()
{
	return xPos;
}

double Monster::getY()
{
	return yPos;
}

void Monster::interactedMonster(unsigned int itemID)
{
	switch(itemID)
	{
	case 3:
		health -= 12;
		break;
	case 4:
		health -= 50;
		break;
	case 6:
		health -= 87;
		break;
	}
	if(!determineToDraw())
	{
		int get = sf::Randomizer::Random(0, 10);
		//int get = 1;
		if(get == 1)
		{
			hPack.newHealthPack(xPos + 0.125, yPos + 0.125, 0.125, 20);
			hPack.GlowEffect.newEffect(xPos + 0.125, yPos + 0.125, 0.25);
		}
	}
}

double Monster::getRotation()
{
	return Rotation;
}

double Monster::getDamage()
{
	return damageOutput;
}

double Monster::getAttackTime()
{
	return attackTimer;
}

void Monster::setAttackTime(double PassTime)
{
	attackTimer = PassTime;
}