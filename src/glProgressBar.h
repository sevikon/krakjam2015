#pragma once
#include "SFML\Graphics.hpp"
#define SPRITES 10

class glProgressBar
{
private:
	sf::Sprite  backgroundSprite[SPRITES];
	sf::Texture backgroundTexture[SPRITES];
	sf::Texture pbTexture;
	sf::Sprite  pbSprite;

	sf::Clock timer;

public: 
	float lava;
	float player1;
	float player2;

	void Load();
	void Init();
	void Update(float player1, float player2);

	/**
	* Draw game on the main window object
	*/
	void Draw(sf::RenderWindow& graphics);

	void DrawLava(sf::RenderWindow& graphics,bool left);
};