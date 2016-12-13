#include "PlayerBullet.h"

#define PI 3.14159265

Bullete::Bullete()
{
	xPos = yPos = NULL;
	xVelocity = 0, yVelocity = 0;
	Texture[0] = Texture[1] = NULL;
	toDraw = false;
	boxRadius = 0.0425;
	liveBullet = false;
}

Bullete::~Bullete()
{
	xPos = yPos = 0.0;
	toDraw = false;
	liveBullet = false;
}

bool Bullete::loadTexture(std::string Filename, int textArrayBit)
{
	sf::Image Image;
	if(!Image.LoadFromFile(Filename))
	{
		return false;
	}
	glGenTextures(1, &Texture[textArrayBit]);
	glBindTexture(GL_TEXTURE_2D, Texture[textArrayBit]);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image.GetWidth(), Image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	std::cout << "Bullet Texture: " << textArrayBit << " loaded" << std::endl;
	return true;
}

void Bullete::registerBullet(double pAngle, double xPos, double yPos, double elapsedTime)
{
	this->xPos = xPos;
	this->yPos = yPos;
	xVelocity = (cos(pAngle*PI/180))*2;
	yVelocity = (sin(pAngle*PI/180))*2;
	this->xPos += xVelocity*elapsedTime;
	this->yPos += yVelocity*elapsedTime;
	liveBullet = true;
	Rotation = pAngle - 90;
}

void Bullete::updateBullet(double elapsedTime)
{
	xPos += xVelocity*elapsedTime;
	yPos += yVelocity*elapsedTime;
}

bool Bullete::bulletCollision(double xPos, double yPos, double boxRadius)
{
	if(liveBullet)
	{
		if(toDraw)
		{
			if(xPos >= this->xPos - boxRadius && xPos + boxRadius <= this->xPos + boxRadius && yPos >= this->yPos - boxRadius && yPos + boxRadius <= this->yPos + boxRadius)
			{
				return true;
			}
			return false;
		}
	}
	return false;
}

bool Bullete::determineToDraw(double xPos, double yPos)
{
	if(liveBullet)
	{
	double DistanceForm = (pow((this->xPos) - xPos, 2) + pow((this->yPos) - yPos, 2));
	DistanceForm = sqrt(DistanceForm);
	if(DistanceForm > 3)
	{
		unregisterBullet();
		return false;
	}
	else
	{
		toDraw = true;
		return true;
	}
	}
	else
	{
		unregisterBullet();
		return false;
	}
}

void Bullete::drawBullet()
{
	if(liveBullet)
	{
		if(toDraw)
		{
			glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_COLOR_MATERIAL);
			glTranslatef(xPos, yPos, 0);
			glRotatef(Rotation, 0, 0, 1);
			glTranslatef(-xPos, -yPos, 0);
			glEnable(GL_TEXTURE_2D);
			switch(bType)
			{
			case Bullete::ENERGY:
				glBindTexture(GL_TEXTURE_2D, Texture[0]);
				break;
			case Bullete::EXPLOSIVE:
				glBindTexture(GL_TEXTURE_2D, Texture[1]);
				break;
			}
			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
				glTexCoord2d(0, 0); glVertex3f(xPos - boxRadius, yPos - boxRadius, 0);
				glTexCoord2d(1, 0); glVertex3f(xPos + boxRadius, yPos - boxRadius, 0);
				glTexCoord2d(1, 1); glVertex3f(xPos + boxRadius, yPos + boxRadius, 0);
				glTexCoord2d(0, 1); glVertex3f(xPos - boxRadius, yPos + boxRadius, 0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glPopMatrix();
		}
	}
}

void Bullete::setTexture(GLuint Texture, int textArrayBit)
{
	this->Texture[textArrayBit] = Texture;
}

GLuint Bullete::getTexture(int textArrayBit)
{
	return Texture[textArrayBit];
}

bool Bullete::isLiveBullet()
{
	return liveBullet;
}

void Bullete::unregisterBullet()
{
	xPos = yPos = 0;
	xVelocity = yVelocity = 0;
	liveBullet = false;
	toDraw = false;
	Rotation = 0;
}

void Bullete::setBulletType(bulletType bulType)
{
	bType = bulType;
}

Bullete::bulletType Bullete::getBulletType()
{
	return bType;
}