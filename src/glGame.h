#pragma once
#include "SFML\Graphics.hpp"
#include "glMainMenu.h"
#include "glHero.h"
#include "glTiledLoader.h"
#include "glBoard.h"
#include "glHandleMusic.h"
#include "glProgressBar.h"
#include "glBullet.h"
#include "glScore.h"

#define GRAVITY 10.f

class glGame
{
private:
	sf::Sprite backgroundSprite;
	sf::Sprite gameOverBackgroundSprite;
	sf::Texture backgroundTexture;
	sf::Texture gameOverBackground;
	glBoard gBoard;
	glProgressBar gProgressBar;
	sf::View player1View;
	sf::View player2View;
	glMainMenu mainMenu;
	glMainMenu::MenuResult chosenOption;
	
	glScore score;


	bool playerLeftOnLadder;
	bool playerRightOnLadder;


	glHero heroLeft;
	glHero heroRight;

	glHandleMusic musicObject;
	//glBullet bullet;

	glBullet bulletsLeft[10];
	glBullet bulletsRight[10];
	//std::vector<glBullet> glBulletsVec;

	enum GAME_STATE {MENU, GAMEPLAY, GAMEOVER, WIN} gameState;
	bool isMenu, isPlaying, isGameOver, isWin;
	void DrawGameOver(sf::RenderWindow& graphics);

	int level;


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
	bool Win();
	bool GameOver();

	void GameStateWin();
	void GameStateGameOver();
	void CheckColisions();

	/**
	* Draw game on the main window object
	*/
	void Draw(sf::RenderWindow& graphics);
	
	/**
	* Handle concrete event
	*/
	void HandleEvent(sf::Event event);
};