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

	float mAngle;

public: 
	void Load();
	void Update();
	void Init(sf::RenderWindow& window);

	/**
	* Draw game on the main window object
	*/
	void Draw(sf::RenderWindow& graphics, sf::Vector2f pos,sf::Vector2f size, bool left,sf::Vector2f herol,sf::Vector2f heror);

	glTiledLoader& getTileManager();
};