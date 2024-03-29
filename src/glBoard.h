#pragma once
#include "SFML\Graphics.hpp"
#include "glBoard.h"
#include "glTiledLoader.h"

#define SPRITES 100

class glBoard
{
private:
	sf::Sprite backgroundSprite[SPRITES];
	sf::Texture backgroundTexture[SPRITES];
	sf::Texture progressBarTexture;
	glTiledLoader mTileManager;

	float mAngle;

public: 
	void Load();
	void Update();
	void Init(int level);
	void ChangeLevel(int level);

	/**
	* Draw game on the main window object
	*/
	void Draw(sf::RenderWindow& graphics, sf::Vector2f pos,sf::Vector2f size, bool left,sf::Vector2f herol,sf::Vector2f heror);

	void DrawPressStackProgressBar(sf::RenderWindow& graphics, float progress, float posx, float posy);

	glTiledLoader& getTileManager();
};