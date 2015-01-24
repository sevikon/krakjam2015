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
	glTiledLoader mTileManager;

public: 
	void Load();
	void Update();
	void Init(sf::RenderWindow& window);

	/**
	* Draw game on the main window object
	*/
	void Draw(sf::RenderWindow& graphics, sf::Vector2f pos,sf::Vector2f size, bool left);

	glTiledLoader& getTileManager();
};