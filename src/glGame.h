#pragma once
#include "SFML\Graphics.hpp"

class glGame
{
private:
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	sf::View player1View;
	sf::View player2View;

public: 
	void ShowScores();
	void ShowDemo();
	void Load();
	void Init(sf::RenderWindow& window);
	void Update();

	/**
	* Draw game on the main window object
	*/
	void Draw(sf::RenderWindow& graphics);
	
	/**
	* Handle concrete event
	*/
	void HandleEvent(sf::Event event);
};