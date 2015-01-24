#pragma once
#include "SFML\Graphics.hpp"
#include "glMainMenu.h"
#include "glTiledLoader.h"
#include "glBoard.h"

class glGame
{
private:
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	glTiledLoader gTiledLoader;
	glBoard gBoard;
	sf::View player1View;
	sf::View player2View;
	glMainMenu mainMenu;
	glMainMenu::MenuResult chosenOption;
	enum GAME_STATE {MENU, GAMEPLAY} gameState;

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