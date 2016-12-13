#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Terrain.h"
#include <fstream>

std::string loadFile[2];

#pragma warning(disable : 4244)

void TerrainManager::drawTerrain()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture[0]);
     for(int i = 0; i < 2601; i++)
     {
	  glPushMatrix();
      glBegin(GL_QUADS);
	   glTexCoord2d(0.0, 0.0); glVertex2f(TerrainData[i].xPos, TerrainData[i].yPos);
	   glTexCoord2d(0.0, 1.0); glVertex2f(TerrainData[i].xPos, TerrainData[i].yPos + 0.25);
	   glTexCoord2d(1.0, 1.0); glVertex2f(TerrainData[i].xPos + 0.2, TerrainData[i].yPos + 0.25);
	   glTexCoord2d(1.0, 0.0); glVertex2f(TerrainData[i].xPos + 0.2, TerrainData[i].yPos);
      glEnd();
	  glPopMatrix();
     }
	 glDisable(GL_TEXTURE_2D);
}

bool TerrainManager::readTerrainCofig()
{
	std::ifstream inFile;
	inFile.open("Terrain.conf");
	inFile >> loadFile[0];
	inFile >> loadFile[1];
	std::cout << loadFile[0] << std::endl << loadFile[1] << std::endl;
	if(loadTerrainPositions(loadFile[0]))
	{
		if(loadTerrainType(loadFile[1]))
		{
			if(loadTextures("Grass.png"))
			{
				std::cout << "Loaded" << std::endl;
				inFile.close();
				return true;
			}
		}
	}
	return false;
}

bool TerrainManager::loadTerrainPositions(std::string Filename)
{
	std::ifstream loadFile;
	loadFile.open(Filename);
	if(loadFile.is_open())
	{
		for(int i = 0; i < 2601; i++)
		{
			loadFile >> TerrainData[i].xPos;
			loadFile >> TerrainData[i].yPos;
		}
		loadFile.close();
		return true;
	}
	else
		return false;
	return false;
}

bool TerrainManager::loadTerrainType(std::string Filename)
{
	std::ifstream loadFile;
	loadFile.open(Filename);
	int terrainType[50];
	if(loadFile.is_open())
	{
		for(int i = 0; i < 2601; i++)
		{
			loadFile >> terrainType[i];
			/*switch(terrainType[i])
			{
			case 0:
				TerrainData[i].TerrainType = vec2::GRASS;
				break;
			case 1:
				TerrainData[i].TerrainType = vec2::FENCE;
				break;
			default:
				TerrainData[i].TerrainType = vec2::GRASS;
				break;
			}*/
		}
		loadFile.close();
		return true;
	}
	else
		return false;
	return false;
}

void TerrainManager::writeTerrainPositions(std::string Filename)
{
	std::ofstream outFile;
	outFile.open(Filename);
	if(outFile.is_open())
	{
		for(int i = 0; i < 2601; i++)
		{
			outFile << TerrainData[i].xPos << std::endl;
			outFile << TerrainData[i].yPos << std::endl;
		}
		outFile.flush();
		outFile.close();
	}
}

void TerrainManager::writeTerrainConfig()
{
	std::ofstream outFile;
	outFile.open("Terrain.conf");
	if(outFile.is_open())
	{
		outFile << "TerrainPosition.inv" << std::endl;
		outFile << "TerrainType.inv" << std::endl;
		outFile << "TerrainTexture.inv" << std::endl;
		writeTerrainPositions("TerrainPosition.inv");
		//writeNewTerrainPositions("TerrainPosition.inv");
		outFile.close();
	}
}

void TerrainManager::createRenderList()
{
	renderList = glGenLists(1);
	glNewList(renderList, GL_COMPILE);
	drawTerrain();
	glEndList();
}

void TerrainManager::renderTerrain()
{
	glCallList(renderList);
}

void TerrainManager::writeNewTerrainPositions(std::string Filename)
{
	std::ofstream outFile;
	outFile.open(Filename);
	double newX = -0.2, newY = 0;
	const double newLine = 9.8;
	for(int i = 0; i < 2601; i++)
	{
		newX += 0.2;
		outFile << newX << std::endl;
		outFile << newY << std::endl;
		outFile.flush();
		if(newX >= 9.8)
		{
			newX = 0;
			newY += 0.25;
			std::cout << "Written Line: " << i << std::endl;
		}
	}
}

bool TerrainManager::loadTextures(std::string Filename)
{
	sf::Image Image;
	if(!Image.LoadFromFile(Filename))
	{
		return false;
	}
	glGenTextures(1, &Texture[0]);
	glBindTexture(GL_TEXTURE_2D, Texture[0]);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image.GetWidth(), Image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return true;
}


