#include "GlowEffect.h"
#include <iostream>

Particle_GlowEffect::Particle_GlowEffect()
{
	alphaValue = 0;
	toDraw = false;
	objPosition = NULL;
	amp = false;
}

Particle_GlowEffect::Particle_GlowEffect(std::string Filename)
{
	alphaValue = 0;
	toDraw = false;
	objPosition = NULL;
	amp = false;
}

Particle_GlowEffect::~Particle_GlowEffect()
{
	this->deleteTexture();
	alphaValue = 0;
	toDraw = amp = false;
	objPosition = NULL;
}

void Particle_GlowEffect::newEffect(double xPos, double yPos, double boxRadius)
{
	objPosition.xPos = xPos;
	objPosition.yPos = yPos;
	objPosition.boxRadius = boxRadius;
	alphaValue = 0;
	toDraw = true;
	amp = true;
	loadTexture("GlowEffect.png");
}

void Particle_GlowEffect::newEffect(vec2 objPosition)
{
	this->objPosition = objPosition;
	alphaValue = 0;
	toDraw = true;
	amp = true;
	loadTexture("GlowEffect.png");
}

double Particle_GlowEffect::getX()
{
	return objPosition.xPos;
}

double Particle_GlowEffect::getY()
{
	return objPosition.yPos;
}

void Particle_GlowEffect::removeEffect()
{
	objPosition = NULL;
	toDraw = false;
	alphaValue = 0;
	deleteTexture();
}

void Particle_GlowEffect::updateEffect(double timePassed)
{
	if(toDraw)
	{
		if(amp && alphaValue != 1)
		{
			alphaValue += timePassed/2;
		}
		if(amp && alphaValue >= 1)
		{
			amp = false;
			alphaValue -= timePassed/2;
		}
		if(!amp && alphaValue != 0)
		{
			alphaValue -= timePassed/2;
		}
		if(!amp && alphaValue <= 0)
		{
			amp = true;
			alphaValue += timePassed/2;
		}
	}
}

void Particle_GlowEffect::drawEffect(double timePassed)
{
	if(toDraw)
	{
		updateEffect(timePassed);
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, getTexture());
		glColor4f(1, 1, 1, alphaValue);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 0); glVertex3f(objPosition.xPos - objPosition.boxRadius, objPosition.yPos - objPosition.boxRadius, 0);
			glTexCoord2d(0, 1); glVertex3f(objPosition.xPos - objPosition.boxRadius, objPosition.yPos + objPosition.boxRadius, 0);
			glTexCoord2d(1, 1); glVertex3f(objPosition.xPos + objPosition.boxRadius, objPosition.yPos + objPosition.boxRadius, 0);
			glTexCoord2d(1, 0); glVertex3f(objPosition.xPos + objPosition.boxRadius, objPosition.yPos - objPosition.boxRadius, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}
