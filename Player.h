#include <SFML/Graphics.hpp>
#include "vec2.h"
#include <Windows.h>
#include <gl/GL.h>

#ifndef MAINPLAYER
#define MAINPLAYER

class Player
{
public:
	unsigned int getHealth();
	unsigned int* getHealth(bool YouNeed);
	double getX();
	double getY();
	unsigned int getHeldItem();
	double getRotation();
	Player();
	~Player();
	void renderPlayer();
	bool loadPlayerTexture(std::string Filename);
	void setPlayerPosition(double xPos, double yPos);
	bool mCollision(vec2::tType TerrType);
	void figureOutRotation(double mouseX, double mouseY);
	int availAmmo, reserveAmmo, maxClip;
	double fireRate;
	void setHeldItem(unsigned int HeldItem);
	void setHealth(unsigned int HEALTH);
	int barricadeAmount;
protected:
	unsigned int heldItem, inventory[20];
	unsigned int surfaceArea;
	double Rotation;
	GLuint Texture;
	unsigned int health;
private:
	double xPos, yPos;
	const double zPos;
};
#endif