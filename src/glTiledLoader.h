#pragma once

#include <SFML/Graphics.hpp>
#include "glHero.h"
#include "glTiled.h"
#define GROUND_MIN 1
#define GROUND_MAX 20
#define LADDER_MIN 21
#define LADDER_MAX 23
#define OBJECTS_MIN 24
#define FREE 99

class glTiledLoader
{	
private:
	// private data
	bool mBoolean;
	int** board;

	// size of the currently loaded map
	int amountOfRows;
	int amountOfColumns;
	 
public:
	std::vector<std::vector <int> > vec;
	std::vector<std::vector <glTiled> > vecTiled;
	glTiledLoader();
	~glTiledLoader(){};
	void Load();
	void Init();
	void Draw();
	void Update();
	void UpdateHighscore(int score);
	void loadMap(int number);
	void getTiledValue(int x,int y);
	bool isLadder(int x,int y);
	bool isActive(int x,int y);
	bool isWall(int x,int y);
	bool isFree(int x,int y);
	int getValue(int x,int y);
	int getMapWidth();
	int getMapHeight();
	bool intersectsWithWall(glHero& hero);
	bool intersectsWithWallVertically(glHero& hero);
	bool intersectsWithLadder(glHero& hero);
	sf::FloatRect getTileBoundingBox(int row, int col, glHero::PLAYER playerId);
	void setActive(int x,int y);
	float getLowerOpacity(int x,int y);
	void callAssociated();
	glTiled &searchTiled(int c, int type);
		// returns tile coordinates by position
	void getTileCoords(float posX, float posY, glHero::PLAYER playerId, int& tileX, int& tileY);
};