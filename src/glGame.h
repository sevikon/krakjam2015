#pragma once
#include "SFML\Graphics.hpp"
#include "glMainMenu.h"
#include "glHero.h"
#include "glTiledLoader.h"
#include "glBoard.h"
#include "glHandleMusic.h"
#include "glProgressBar.h"
#include "glScore.h"

#define GRAVITY 10.f

class glGame
{
private:
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	glBoard gBoard;
	glProgressBar gProgressBar;
	sf::View player1View;
	sf::View player2View;
	glMainMenu mainMenu;
	glMainMenu::MenuResult chosenOption;
	
	glScore score;

	glHero heroLeft;
	glHero heroRight;

	glHandleMusic musicObject;

	int level;

	enum GAME_STATE {MENU, GAMEPLAY} gameState;
	bool isMenu, isPlaying;

	const static int bornAge;
	const static int level1Age;
	const static int level2Age;
	const static int level3Age;
	const static int level4Age;
	const static int level5Age;

public: 
	void ShowScores();
	void ShowDemo();
	void Load();
	void Init(sf::RenderWindow& window);
	void Update();
	void CheckCollisionBorder();

	/**
	* Draw game on the main window object
	*/
	void Draw(sf::RenderWindow& graphics);
	
	/**
	* Handle concrete event
	*/
	void HandleEvent(sf::Event event);
};