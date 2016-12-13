#include "EnergyEffect.h"

Particle_EnergyEffect::Particle_EnergyEffect()
{
	xPos = yPos = alphaTransparency = 0;
	toDraw = false;
	secondsToDeath = 0;
}

Particle_EnergyEffect::~Particle_EnergyEffect()
{
	xPos = yPos = alphaTransparency = 0;
	toDraw = false;
	secondsToDeath = 0;
	this->deleteTexture();
}

double Particle_EnergyEffect::getX()
{
	return xPos;
}

double Particle_EnergyEffect::getY()
{
	return yPos;
}

void Particle_EnergyEffect::newEffect(double xPos, double yPos, double secondTimer, double boxRadius, double monsterRotation)
{
	this->xPos = xPos;
	this->yPos = yPos;
	secondsToDeath = secondTimer;
	alphaTransparency = 0.0;
	toDraw = true;
	this->boxRadius = boxRadius;
	totalTime = secondTimer;
	Rotation = monsterRotation;
}

void Particle_EnergyEffect::drawEffect()
{
	if(toDraw)
	{
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(xPos + (boxRadius/2), yPos + (boxRadius/2), 0);
		glRotatef(Rotation, 0, 0, 1);
		glTranslatef(-xPos - (boxRadius/2), -yPos - (boxRadius/2), 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->getTexture());
		glColor4f(1, 1, 1, alphaTransparency);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 0); glVertex3f(xPos, yPos, 0);
			glTexCoord2d(0, 1); glVertex3f(xPos , yPos + boxRadius, 0);
			glTexCoord2d(1, 1); glVertex3f(xPos + boxRadius, yPos + boxRadius, 0);
			glTexCoord2d(1, 0); glVertex3f(xPos + boxRadius, yPos, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}

bool Particle_EnergyEffect::determineToDraw()
{
	if(secondsToDeath <= 0)
	{
		toDraw = false;
		return false;
	}
	return true;
}

void Particle_EnergyEffect::updateEffect(double timePassed, double xPos, double yPos, double monsterRotation)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->secondsToDeath -= timePassed;
	alphaTransparency = secondsToDeath/totalTime;
	Rotation = monsterRotation;
}

void Particle_EnergyEffect::deleteEffect()
{
	xPos = yPos = alphaTransparency = 0;
	toDraw = false;
	secondsToDeath = 0;
}