#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceHeaders.h"
#include <gl/GL.h>

#pragma warning(disable : 4244)
#pragma warning(disable : 4099)
#define PI 3.141592654

double xPos = 0.0, yPos = 0.0, elapsedTime;
double mouseX, mouseY;
bool runProgram = true;
sf::RenderWindow RW(sf::VideoMode(800, 600, 32), "Project VII - Note: Fix Monster Damage", sf::Style::Resize);
Barricade bCadeGeneric("Barricade.png");
Barricade pBarricade[MAXBARRICADE];
TimedExplosive pTimedExplosive("FireSprite1.png", "FireSprite2.png");
HealthBar healthBar("Bar.png");

void Enable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glOrtho(0, 800, 0, 600, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Disable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void KeyboardIntel(sf::Input& windowInput, double elapsedTime, double timePassed)
{
	if(windowInput.IsKeyDown(sf::Key::D))
	{
		xPos -= 1.001 * elapsedTime;
	}
	else if(windowInput.IsKeyDown(sf::Key::A))
	{
		xPos += 1.001 * elapsedTime;
	}
    if(windowInput.IsKeyDown(sf::Key::W))
	{
		yPos -= 1.001 * elapsedTime;
	}
	else if(windowInput.IsKeyDown(sf::Key::S))
	{
		yPos += 1.001 * elapsedTime;
	}
	if(windowInput.IsMouseButtonDown(sf::Mouse::Left))
	{
		bool runBullet = false;
		while(!runBullet)
		{
			for(int i = 0; i < 60; i++)
			{
				if(MainPlayer.availAmmo > 0)
				{
					if(!pBullet[i].isLiveBullet())
					{
						if(MainPlayer.fireRate <= 0)
						{
							switch(MainPlayer.getHeldItem())
							{
							case 3:
								pBullet[i].registerBullet(MainPlayer.getRotation(), MainPlayer.getX() + 0.125, MainPlayer.getY() + 0.125, elapsedTime);
								runBullet = true;
								MainPlayer.availAmmo -= 1;
								pBullet[i].setBulletType(Bullete::ENERGY);
								MainPlayer.fireRate = 0.225;
								break;
							case 4:
								pBullet[i].registerBullet(MainPlayer.getRotation(), MainPlayer.getX() + 0.125, MainPlayer.getY() + 0.125, elapsedTime);
								runBullet = true;
								MainPlayer.availAmmo -= 1;
								pBullet[i].setBulletType(Bullete::EXPLOSIVE);
								MainPlayer.fireRate = 1.0025;
								break;
							}
						}
					}
				}
			}
			runBullet = true;
		}
	}
	MainPlayer.setPlayerPosition(-xPos, -yPos);
	MainPlayer.fireRate -= timePassed;
}

void runGUI()
{
	    Enable2D();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ButtonTexture);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
			glTexCoord2d(0.0, 1.0); glVertex3f(25, 50, 0);
			glTexCoord2d(1.0, 1.0); glVertex3f(125, 50, 0);
			glTexCoord2d(1.0, 0.0); glVertex3f(125, 150, 0);
			glTexCoord2d(0.0, 0.0); glVertex3f(25, 150, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		healthBar.updateHealthBar((double)MainPlayer.getHealth());
		healthBar.drawHealthBar();
		Disable2D();
}

bool LoadTexture()
{
	sf::Image Image;
	if(!Image.LoadFromFile("StuckButton.png"))
		return false;
	glGenTextures(1, &ButtonTexture);
	glBindTexture(GL_TEXTURE_2D, ButtonTexture);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image.GetWidth(), Image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return true;
}

bool loadMouseTexture()
{
	sf::Image Image;
	if(!Image.LoadFromFile("Mouse.png"))
		return false;
	glGenTextures(1, &MouseTexture);
	glBindTexture(GL_TEXTURE_2D, MouseTexture);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image.GetWidth(), Image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return true;
}

void customMouse(sf::RenderWindow& RW, double mouseX, double mouseY)
{
	RW.ShowMouseCursor(false);
	Enable2D();
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, MouseTexture);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2d(mouseX - 15, mouseY - 15);
		glTexCoord2d(0, 1); glVertex2d(mouseX - 15, mouseY + 15);
		glTexCoord2d(1, 1); glVertex2d(mouseX + 15, mouseY + 15);
		glTexCoord2d(1, 0); glVertex2d(mouseX + 15, mouseY - 15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
	Disable2D();
}

void init()
{
	Terrain.readTerrainCofig();
	Terrain.createRenderList();
	LoadTexture();
	mMonster[0].loadTexture("Monster.png");
	mMonster[0].hPack.loadTexture("HealthPack.png");
	pBullet[0].loadTexture("Bullet.png", 0);
	pBullet[0].loadTexture("MissleRocket.png", 1);
	pEnergyEffect[0].loadTexture("EnergyEffect.png");
	pExplosionEffect[0].loadTexture("ExplosionEffect.png");
	loadMouseTexture();
	double start = 1;
	for(int i = 1; i < 60; i++)
	{
		pBullet[i].setTexture(pBullet[0].getTexture(0), 0);
		pBullet[i].setTexture(pBullet[0].getTexture(1), 1);
	}
	for(int i = 1; i < 40; i++)
	{
		mMonster[i].setTexture(mMonster[0].getTexture());
		mMonster[i].hPack.setTexture(mMonster[0].hPack.getTexture());
	}
	for(int i = 0; i < 40; i++)
	{
		mMonster[i].setMonsterPosition(start, 2);
		start += 0.2;
	}
	for(int i = 1; i < 40; i++)
	{
		pEnergyEffect[i].setTexture(pEnergyEffect[0].getTexture());
		pExplosionEffect[i].setTexture(pExplosionEffect[0].getTexture());
	}
	if(!MainPlayer.loadPlayerTexture("Player.png"))
	{
		RW.Close();
		exit(0);
	}
	healthBar.newHealthBar(650, 150, 100, 100);
}

void TextDisplay()
{
	Test.SetFont(sf::Font::GetDefaultFont());
	Test.SetSize(15);
	Test.SetColor(sf::Color::Red);
	Test.SetScale(2, 2);
	Test.Move(0, 0);
}

int main(int argc, char *argv[])
{
	RW.SetFramerateLimit(60);
	init();
	TextDisplay();
	while(RW.IsOpened())
	{
		elapsedTime = Clock.GetElapsedTime();
		Clock.Reset();
		const sf::Input& windowInput = RW.GetInput();
		KeyboardIntel((sf::Input&)windowInput, RW.GetFrameTime(), elapsedTime);
		while(RW.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
			{
				Terrain.~TerrainManager();
				RW.Close();
				exit(0);
			}
			if(Event.Type == sf::Event::Resized)
			{
				glViewport(0.0, 0.0, Event.Size.Width, Event.Size.Height);
			}
			if(Event.Type == sf::Event::KeyPressed)
			{
				double posX = (MainPlayer.getX() + 0.125) + cos(MainPlayer.getRotation()*PI/180)/4;
				double posY = (MainPlayer.getY() + 0.125) + sin(MainPlayer.getRotation()*PI/180)/4;
				switch(Event.Key.Code)
				{
				case sf::Key::Num3:
					MainPlayer.setHeldItem(3);
					break;
				case sf::Key::Num4:
					MainPlayer.setHeldItem(4);
					break;
				case sf::Key::Num5:
					MainPlayer.setHeldItem(5);
					//bCadeGeneric.newBarricade(posX, posY, 1, MainPlayer.getRotation());
					for(int i = 0; i < MAXBARRICADE; i++)
					{
						if(!pBarricade[i].determineToDraw())
						{
							pBarricade[i].newBarricade(posX, posY, 1, MainPlayer.getRotation());
							break;
						}
					}
					break;
				case sf::Key::Num6:
					MainPlayer.setHeldItem(6);
					for(int i = 0; i < MAXBARRICADE; i++)
					{
						if(!collisionMang.insideAnotherObject(posX, posY, pBarricade[i].getX(), pBarricade[i].getY(), pBarricade[i].getBoxRadius()))
						{
							if(!pTimedExplosive.determineToDraw(RW.GetFrameTime()))
							{
								pTimedExplosive.newTimedExplosive(posX, posY, 6);
							}
						}
					}
					break;
				case sf::Key::Escape:
					Terrain.~TerrainManager();
					MainPlayer.~Player();
					for(int i = 0; i < 60; i++)
					{
						pBullet[i].~Bullete();
					}
					for(int i = 0; i < 40; i++)
					{
						mMonster[i].~Monster();
						pEnergyEffect[i].~Particle_EnergyEffect();
						pExplosionEffect[i].~Particle_ExplosionEffect();
					}
					RW.Close();
					exit(0);
					break;
				case sf::Key::P:
					MainPlayer.availAmmo = 30;
					MainPlayer.reserveAmmo = 600;
					break;
				case sf::Key::R:
					int addSub;
					addSub = MainPlayer.maxClip - MainPlayer.availAmmo;
					if(addSub > MainPlayer.reserveAmmo)
					{
						MainPlayer.availAmmo += MainPlayer.reserveAmmo;
						MainPlayer.reserveAmmo = 0;
					}
					else
					{
						MainPlayer.availAmmo += addSub;
						MainPlayer.reserveAmmo -= addSub;
					}
					break;
				}
			}
			if(Event.Type == sf::Event::MouseButtonReleased)
			{
				mouseX = windowInput.GetMouseX();
				mouseY = windowInput.GetMouseY();
				if(mouseX >= 25 && mouseX <= 125 && mouseY >= 450 && mouseY <= 550)
				{
					std::cout << "Player position set back to (0,0)" << std::endl;
					xPos = yPos = 0.0;
					MainPlayer.setPlayerPosition(0.0, 0.0);
				}
			}
			if(Event.Type == sf::Event::MouseButtonPressed)
			{
				switch(MainPlayer.getHeldItem())
				{
				case 0:
					for(int i = 0; i < 40; i++)
					{
						if(mMonster[i].interactedMonster(-xPos, -yPos, MainPlayer.getHeldItem(), MainPlayer.getRotation()))
						{
							mMonster[i].determineToDraw();
						}
					}
					break;
				case 5:
					break;
				}
			}
		}
		oss.str("");
		oss << "Ammo: " << MainPlayer.availAmmo << "/" << MainPlayer.reserveAmmo;
		amDisp = oss.str();
		Test.SetText(amDisp);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glTranslatef(xPos, yPos, -50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		Terrain.renderTerrain();
		MainPlayer.figureOutRotation(windowInput.GetMouseX(), windowInput.GetMouseY());
		for(int i = 0; i < 40; i++)
		{
			if(mMonster[i].hPack.getToDraw())
			{
				mMonster[i].hPack.drawHealthPack(RW.GetFrameTime());
				mMonster[i].hPack.GlowEffect.drawEffect(RW.GetFrameTime());
				if(collisionMang.distanceBetweenPoints(MainPlayer.getX() + 0.125, mMonster[i].hPack.getX(), MainPlayer.getY() + 0.125, mMonster[i].hPack.getY()) <= 0.125 + mMonster[i].hPack.getBox())
				{
					mMonster[i].hPack.interactedHealthPack(MainPlayer.getHealth(true), 100);
				}
			}
		}
		for(int i = 0; i < 40; i++)
		{
			if(mMonster[i].determineToDraw())
			{
				mMonster[i].renderMonster(MainPlayer.getX(), MainPlayer.getY(), RW.GetFrameTime());
				if(mMonster[i].getAttackTime() <= 0)
				{
					if(mMonster[i].aConf.attackPlayer(mMonster[i].getX(), mMonster[i].getY(), MainPlayer.getX(), MainPlayer.getY(), MainPlayer.getHealth(true), 0.25, mMonster[i].getDamage()))
					{
						mMonster[i].setAttackTime(1.25);
					}
					else
					{
						for(int j = 0; j < MAXBARRICADE; j++)
						{
							double monX, monY;
							monX = mMonster[i].getX() + (cos(mMonster[i].getRotation()*PI/180))/mMonster[i].movementMult;
							monY = mMonster[i].getX() + (sin(mMonster[i].getRotation()*PI/180))/mMonster[i].movementMult;
							if(pBarricade[j].determineToDraw())
							{
								if(mMonster[i].aConf.attackObject(mMonster[i].getX(), mMonster[i].getY(), pBarricade[j].getX(), pBarricade[j].getY(), pBarricade[j].getHealthP(), 0.2, mMonster[i].getDamage()))
								{
									pBarricade[j].interactedBarricade(200);
									mMonster[i].setAttackTime(1.25);
								}
							}
						}
					}
				}
			}
			else
			{
				int x = MainPlayer.getX();
				int y = MainPlayer.getY();
				mMonster[i].reviveMonster(sf::Randomizer::Random(x - 1, x + 1), sf::Randomizer::Random(y - 1, y + 1));
			}
		}
		if(MainPlayer.getHealth() == 0)
		{
			std::cout << "You Died" << std::endl;
			MainPlayer.setPlayerPosition(0, 0);
			xPos = yPos = 0.0;
			MainPlayer.setHealth(100);
			RW.Close();
		}
		if(pTimedExplosive.determineToDraw(RW.GetFrameTime()))
		{
			pTimedExplosive.drawExplosive();
		}
		if(pTimedExplosive.explosionSet)
		{
			int elp = 0;
			for(int i = 0; i < 40; i++)
			{
				if(!pExplosionEffect[i].determineToDraw() && elp < 3)
				{
					pExplosionEffect[i].newEffect(pTimedExplosive.getX() - 0.15, pTimedExplosive.getY() - 0.15, 2, 0.15*4, 0);
					pExplosionEffect[i].randomizeExplosions(pTimedExplosive.getX() - 0.15, pTimedExplosive.getY() - 0.15);
					elp++;
				}
			}
			for(int i = 0; i < 40; i++)
			{
				if(mMonster[i].determineToDraw())
				{
					if(pTimedExplosive.explosionOff(mMonster[i].getX() + 0.125, mMonster[i].getY() + 0.125, 0.125))
					{
						mMonster[i].interactedMonster(6);
					}
				}
			}
			pTimedExplosive.explosionSet = false;
		}
		for(int i = 0; i < MAXBARRICADE; i++)
		{
			pBarricade[i].drawBarricade();
		}
		MainPlayer.renderPlayer();
		for(int i = 0; i < 40; i++)
		{
			if(pEnergyEffect[i].determineToDraw())
			{
				pEnergyEffect[i].updateEffect(RW.GetFrameTime(), mMonster[i].getX(), mMonster[i].getY(), mMonster[i].getRotation());
				if(mMonster[i].determineToDraw())
					pEnergyEffect[i].drawEffect();
				else
					pEnergyEffect[i].deleteEffect();
			}
			else if(pExplosionEffect[i].determineToDraw())
			{
				pExplosionEffect[i].updateEffect(RW.GetFrameTime());
				pExplosionEffect[i].drawEffect();
			}
		}
		for(int i = 0; i < 60; i++)
		{
			if(pBullet[i].determineToDraw(MainPlayer.getX(), MainPlayer.getY()))
			{
				pBullet[i].drawBullet();
				pBullet[i].updateBullet(RW.GetFrameTime());
				for(int j = 0; j < 40; j++)
				{
					if(mMonster[j].determineToDraw())
					{
						if(pBullet[i].bulletCollision(mMonster[j].getX(), mMonster[j].getY(), 0.25))
						{
							pBullet[i].unregisterBullet();
							if(pBullet[i].getBulletType() == Bullete::ENERGY)
							{
								mMonster[j].interactedMonster(3);
							}
							if(!pEnergyEffect[j].determineToDraw() && pBullet[i].getBulletType() == Bullete::ENERGY && MainPlayer.getHeldItem() == 3)
							{
								pEnergyEffect[j].newEffect(mMonster[j].getX(), mMonster[j].getY(), 0.675, 0.25, mMonster[j].getRotation());
								pEnergyEffect[j].drawEffect();
							}
							else if(pBullet[i].getBulletType() == Bullete::EXPLOSIVE && MainPlayer.getHeldItem() == 4)
							{
								mMonster[j].interactedMonster(4);
								pExplosionEffect[j].newEffect(mMonster[j].getX(), mMonster[j].getY(), 1.25, 0.25, mMonster[j].getRotation());
								pExplosionEffect[j].drawEffect();
							}
						}
					}
				}
			}
		}
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		runGUI();
		customMouse((sf::RenderWindow&)RW, windowInput.GetMouseX(), 600 - windowInput.GetMouseY());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		RW.Draw(Test);
		glColor3f(1.0, 1.0, 1.0);
		RW.Display();
	}
}