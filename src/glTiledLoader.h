#pragma once

#include <SFML/Graphics.hpp>
#include "glHero.h"
#include "glTiled.h"


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

		// returns tile coordinates by position
	void getTileCoords(float posX, float posY, glHero::PLAYER playerId, int& tileX, int& tileY);
};