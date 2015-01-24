#pragma once

#include <SFML/Graphics.hpp>
#define HEIGHT 510
#define WIDTH 510

class glTiledLoader
{	
private:
	// private data
	bool mBoolean;
	int** board;
	 
public:
	std::vector<std::vector <int> > vec;
	glTiledLoader();
	~glTiledLoader(){};
	void Load();
	void Init();
	void Draw();
	void UpdateHighscore(int score);
	void loadMap(int number);
	void getTiledValue(int x,int y);
	bool isLadder(int x,int y);
	bool isWall(int x,int y);
	bool isFree(int x,int y);
	int getValue(int x,int y);
};