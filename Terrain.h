#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vec2.h"

#ifndef TERRMANG
#define TERRMANG

class TerrainManager
{
      public:
             bool readTerrainCofig();
             void drawTerrain();
			 TerrainManager() {};
			 ~TerrainManager() {writeTerrainConfig();};
             void writeTerrainConfig();
			 GLuint renderList;
			 GLuint Texture[4];
			 void createRenderList();
			 void renderTerrain();
			 void writeNewTerrainPositions(std::string);
			 bool loadTextures(std::string Filename);
      protected:
             void writeTerrainType(std::string Filename);
             void writeTerrainPositions(std::string Filename);
             bool loadTerrainType(std::string Filename);
             bool loadTerrainPositions(std::string Filename);
      private:
		     vec2 TerrainData[2601];
};
#endif