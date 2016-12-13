#include "HUD_Generic.h"

GenericHUD::GenericHUD()
{
	this->loadTexture("Generic_HUD");
	objPosition.xPos = objPosition.yPos = xRad = yRad = 0;
}

GenericHUD::GenericHUD(std::string Filename)
{
	this->loadTexture(Filename);
	objPosition.xPos = objPosition.yPos = xRad = yRad = 0;
}

GenericHUD::~GenericHUD()
{
	this->deleteTexture();
	objPosition.xPos = objPosition.yPos = xRad = yRad = 0;
}

void GenericHUD::newHUD(double xPos, double yPos, double xRad, double yRad)
{
	objPosition.xPos = xPos;
	objPosition.yPos = yPos;
	this->xRad = xRad;
	this->yRad = yRad;
}

void GenericHUD::drawHUD()
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture());
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3f(objPosition.xPos - xRad, objPosition.yPos - yRad, 0);
		glTexCoord2d(0, 1); glVertex3f(objPosition.xPos - xRad, objPosition.yPos + yRad, 0);
		glTexCoord2d(1, 1); glVertex3f(objPosition.xPos + xRad, objPosition.yPos + yRad, 0);
		glTexCoord2d(1, 0); glVertex3f(objPosition.xPos + xRad, objPosition.yPos - yRad, 0);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

double GenericHUD::getX()
{
	return objPosition.xPos;
}

double GenericHUD::getY()
{
	return objPosition.yPos;
}