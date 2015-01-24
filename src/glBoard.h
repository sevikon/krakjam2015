#pragma once
#include "SFML\Graphics.hpp"
#include "glBoard.h"
#include "glTiledLoader.h"

#define SPRITES 10

class glBoard
{
private:
	sf::Sprite backgroundSprite[SPRITES];
	sf::Texture backgroundTexture[SPRITES];

public: 
	void Load();
	void Init(sf::RenderWindow& window);

	/**
	* Draw game on the main window object
	*/
	void Draw(sf::RenderWindow& graphics, sf::Vector2f pos,sf::Vector2f size,glTiledLoader &gTiledLoader, bool left);
};