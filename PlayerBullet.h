#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>

#ifndef SUCKITREDEFINITION
#define SUCKITREDEFINITION
//I could probably use this for other bullet classes too ... I'm a fool at programming. 
class Bullete
{
public:
	Bullete();
	~Bullete();
	void registerBullet(double playerAngle, double xPos, double yPos, double elapsedTime);
	void updateBullet(double elapsedTime);
	bool bulletCollision(double xPos, double yPos, double boxRadius);
	bool loadTexture(std::string Filename, int textArrayBit);
	bool determineToDraw(double xPos, double yPos);
	void drawBullet();
	void setTexture(GLuint Texture, int textArrayBit);
	GLuint getTexture(int textArrayBit);
	bool isLiveBullet();
	void unregisterBullet();
	enum bulletType{ENERGY, EXPLOSIVE, LEAD, EXTENDED};
	void setBulletType(bulletType type);
	bulletType getBulletType();
protected:
	double xVelocity, yVelocity;
	GLuint Texture[2];
	bool liveBullet;
	double Rotation;
	bulletType bType;
private:
	double xPos, yPos;
	double boxRadius;
	bool toDraw;
};
#endif