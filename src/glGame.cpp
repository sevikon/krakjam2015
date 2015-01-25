#include "glGame.h"
#include <stdio.h>
#include "glUtils.h"
#include "glSettings.h"
#include "glTiled.h"
#include <iostream>
#include <stdlib.h>

// params

const  int glGame::bornAge = 36;
const  int glGame::level1Age = 147;
const  int glGame::level2Age = 231;
const  int glGame::level3Age = 302;
const  int glGame::level4Age = 733;
const  int glGame::level5Age = 1076;

const float DELTA = 1.0f / 60.0f;

void glGame::Load()
{

	backgroundTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "sky.png"));
	backgroundSprite.setTexture(backgroundTexture);

	gProgressBar.Load();

	heroLeft.Load(0);
	heroRight.Load(1);

	gBoard.Load();

	score.Load();


	bulletTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "bullet.png"));
	warningTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "warning.png"));

	level = 1;

}

void glGame::Init(sf::RenderWindow& window)
{
	gProgressBar.Init();

	//wczytanie mapy
	printf("-----------------------------------------------------\n");
	printf("Zaczynamy nowa gre.\n");
	printf("-----------------------------------------------------\n");

	gBoard.Init(window);

	bulletsVecLeft.clear();
	bulletsVecRight.clear();

	player1View.setSize(sf::Vector2f(window.getSize().x/2.f, window.getSize().y/1.f));
	player2View.setSize(sf::Vector2f(window.getSize().x/2.f, window.getSize().y)/1.f);
	player1View.setCenter(player1View.getSize().x/2.f, gBoard.getTileManager().getMapHeight()-384);
	player2View.setCenter(player2View.getSize().x/2.f, gBoard.getTileManager().getMapHeight()-384);

	// player 2 (right side of the screen)
	player2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));

	// player 1 (left side of the screen)
	player1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	heroLeft.Init(100, gBoard.getTileManager().getMapHeight() - 64 - heroLeft.getHeight(), player1View, glHero::PLAYER::FST);
	heroRight.Init(500, gBoard.getTileManager().getMapHeight() - 64 - heroRight.getHeight(), player2View, glHero::PLAYER::SND);

	playerLeftOnLadder = playerRightOnLadder = false;

	gameState = GAME_STATE::MENU;
	musicObject.HandleMusic();
	isMenu = false;
	isPlaying = false;
	isGameOver = false;
	isWin = false;

	bulletsTimerLeft =  0.0f;
	bulletsTimerRight = 0.0f;

<<<<<<< HEAD


	bulletsBoundLeft = rand() % 10 + 20;
	bulletsBoundRight = rand() % 10 + 20;
=======
	bulletsBoundLeft = rand() % 15 + 20;
	bulletsBoundRight = rand() % 15 + 20;
>>>>>>> 48701f15889ae0afbcdfafbda010c872dfbb3818

	score.Init(0);
}

bool glGame::Win()
{	
	bool win = false;

	if(heroLeft.position.y < 50 && heroRight.position.y < 50){
		win = true;}

	return win;
}

void glGame::GetReleasedLeft() {
	cout<<"KONIEC"<<endl;
	float x = heroLeft.position.x+heroLeft.getWidth()/2;
	float y = heroLeft.position.y+heroLeft.getHeight()/2;
	int a,b;
	gBoard.getTileManager().getTileCoords(x,y,heroLeft.playerId, a, b);
	gBoard.getTileManager().runActionOnAssociatedLasersShowAgain(a, b);
}

void glGame::GetReleasedRight(){
	cout<<"KONIEC"<<endl;
	float x = heroRight.position.x+heroRight.getWidth()/2;
	float y = heroRight.position.y+heroRight.getHeight()/2;
	int a,b;
	gBoard.getTileManager().getTileCoords(x,y,heroRight.playerId, a, b);
	gBoard.getTileManager().runActionOnAssociatedLasersShowAgain(a, b);
}

bool glGame::GameOver()
{	
	bool gameOver = false;

	if(heroLeft.death == true && heroRight.death == true){
		gameOver = true;}

	return gameOver;
}

void glGame::GameStateWin()
{
	gameState = GAME_STATE::WIN;
}

void glGame::GameStateGameOver()
{
	gameState = GAME_STATE::GAMEOVER;
}

void glGame::Update()
{	
	glTiledLoader& tileManager = gBoard.getTileManager();
	gBoard.Update();

	if (!heroLeft.death)
	{
		// player 1 movement

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			float x = heroLeft.position.x+heroLeft.getWidth()/2;
			float y = heroLeft.position.y+heroLeft.getHeight()/2;
			int a,b;
			gBoard.getTileManager().getTileCoords(x,y,heroLeft.playerId, a, b);
			gBoard.getTileManager().runActionOnAssociated(a, b);
			gBoard.getTileManager().runActionOnAssociatedLasers(a, b);
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			heroLeft.Update(glHero::LEFT);
			if(gBoard.getTileManager().blockedByObstacleOnLeftSide(heroLeft))
				heroLeft.UpdateReverse(glHero::LEFT);
			playerLeftOnLadder = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && tileManager.intersectsWithLadder(heroLeft) )
		{
			heroLeft.Update(glHero::CLIMBUP);
			playerLeftOnLadder = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			heroLeft.Update(glHero::RIGHT);
			if(gBoard.getTileManager().blockedByObstacleOnRightSide(heroLeft))
				heroLeft.UpdateReverse(glHero::RIGHT);
			playerLeftOnLadder = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && tileManager.intersectsWithLadder(heroLeft))
		{
			heroLeft.Update(glHero::CLIMBDOWN);
			if(gBoard.getTileManager().intersectsWithWall(heroLeft))
				heroLeft.UpdateReverse(glHero::CLIMBDOWN);
			playerLeftOnLadder = true;
		}
	
		if (heroLeft.position.x < 0){
			heroLeft.Update(glHero::LEFTBORDER);
		}
		if (heroLeft.position.x > player1View.getSize().x - heroLeft.getWidth()){
			heroLeft.Update(glHero::RIGHTBORDER);
		}

		if(!playerLeftOnLadder)
		{
			// gravity
			heroLeft.Update(glHero::FALL);
			if(gBoard.getTileManager().intersectsWithWall(heroLeft))
				heroLeft.UpdateReverse(glHero::FALL);
		}
	} else
		heroLeft.Update(glHero::NONE);

	// player 2 movement

	if (!heroRight.death)
	{
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			float x = heroRight.position.x+heroRight.getWidth()/2;
			float y = heroRight.position.y+heroRight.getHeight()/2;
			int a,b;
			gBoard.getTileManager().getTileCoords(x,y,heroRight.playerId,a,b);
			gBoard.getTileManager().runActionOnAssociated(a,b);
			gBoard.getTileManager().runActionOnAssociatedLasers(a,b);
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			heroRight.Update(glHero::LEFT);
			if(gBoard.getTileManager().blockedByObstacleOnLeftSide(heroRight))
				heroRight.UpdateReverse(glHero::LEFT);
			playerRightOnLadder = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && tileManager.intersectsWithLadder(heroRight))
		{
			heroRight.Update(glHero::CLIMBUP);
			playerRightOnLadder = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			heroRight.Update(glHero::RIGHT);
			if(gBoard.getTileManager().blockedByObstacleOnRightSide(heroRight))
				heroRight.UpdateReverse(glHero::RIGHT);
			playerRightOnLadder = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && tileManager.intersectsWithLadder(heroRight))
		{
			heroRight.Update(glHero::CLIMBDOWN);
			if(gBoard.getTileManager().intersectsWithWall(heroRight))
				heroRight.UpdateReverse(glHero::CLIMBDOWN);
			playerRightOnLadder = true;
		}

		if (heroRight.position.x < 0){
			heroRight.Update(glHero::LEFTBORDER);
		}
		if (heroRight.position.x > player1View.getSize().x - heroRight.getWidth()){
			heroRight.Update(glHero::RIGHTBORDER);
		}
	
		if(!playerRightOnLadder)
		{
			// gravity
			heroRight.Update(glHero::FALL);
			if(gBoard.getTileManager().intersectsWithWall(heroRight))
				heroRight.UpdateReverse(glHero::FALL);
		}
	} else
		heroRight.Update(glHero::NONE);

	// updating bullets

	for (int i = 0; i < bulletsVecLeft.size(); ++i) {
		bulletsVecLeft.at(i).Update();

		if (bulletsVecLeft.at(i).mOpacity <= 0)
		{
			bulletsVecLeft.erase(bulletsVecLeft.begin() + i); --i;
		}
	}

	for (int i = 0; i < bulletsVecRight.size(); ++i) {
		bulletsVecRight.at(i).Update();

		if (bulletsVecRight.at(i).mOpacity <= 0)
		{
			bulletsVecRight.erase(bulletsVecRight.begin() + i); --i;
		}
	}

	bulletsTimerLeft += DELTA;

	if (bulletsTimerLeft > bulletsBoundLeft)
	{
		bulletsVecLeft.push_back(glBullet());
		bulletsVecLeft.at(bulletsVecLeft.size() - 1).Init(player1View.getCenter().y + 384, &bulletTexture, &warningTexture);

		bulletsTimerLeft = 0.0f;
		bulletsBoundLeft = rand() % 15 + 20;
	}

	bulletsTimerRight += DELTA;

	if (bulletsTimerRight > bulletsBoundRight)
	{
		bulletsVecRight.push_back(glBullet());
		bulletsVecRight.at(bulletsVecRight.size() - 1).Init(player2View.getCenter().y + 384, &bulletTexture, &warningTexture);

		bulletsTimerRight = 0.0f;
		bulletsBoundRight = rand() % 15 + 20;
	}

	CheckColisions();

	// progress bar

	gProgressBar.Update(heroLeft.position.y,heroRight.position.y);

	// updating the camera

	float y1 = heroLeft.position.y + heroLeft.getHeight() / 2;
	float y2 = heroRight.position.y + heroRight.getHeight() / 2;

	if (y1 > gBoard.getTileManager().getMapHeight() - 384)
		y1 = gBoard.getTileManager().getMapHeight() - 384;
	if (y2 > gBoard.getTileManager().getMapHeight() - 384)
		y2 = gBoard.getTileManager().getMapHeight() - 384;

	if (y1 < 384)
		y1 = 384;
	if (y2 < 384)
		y2 = 384;

	player1View.setCenter(player1View.getCenter().x, y1);
	player2View.setCenter(player2View.getCenter().x, y2);

	// Death in lava

	if(heroRight.position.y + heroRight.getHeight() - 170 > gProgressBar.lava){
		heroRight.death = true;}
	if(heroLeft.position.y + heroLeft.getHeight() - 170 > gProgressBar.lava){
		heroLeft.death = true;}

	// updating score

	float progress = (float(gBoard.getTileManager().getMapHeight() - min(player1View.getCenter().y, player2View.getCenter().y) - 384) / float(gBoard.getTileManager().getMapHeight() - 768.0f));
	
	switch (level)
	{
	
	case 1:
		score.SetCurrentScore(bornAge + progress * (level1Age - bornAge));
		break;
	case 2:
		score.SetCurrentScore(level1Age + progress * (level2Age - level1Age));
		break;
	case 3:
		score.SetCurrentScore(level2Age + progress * (level3Age - level2Age));
		break;
	case 4:
		score.SetCurrentScore(level3Age + progress * (level4Age - level3Age));
		break;
	case 5:
		score.SetCurrentScore(level4Age + progress * (level5Age - level4Age));
		break;
		
	}

}

void glGame::Draw(sf::RenderWindow& graphics)
{		
	graphics.setView(graphics.getDefaultView());

	double pos = 0;

	switch(gameState)
	{
		case GAME_STATE::MENU:
			if(!isMenu){
				musicObject.StopAll();
				musicObject.MusicMenu.play();
				isMenu = true;
			}
			chosenOption = mainMenu.Show(graphics, graphics.getSize().x, graphics.getSize().y);
			switch(chosenOption) 
			{
				case glMainMenu::Exit:
					graphics.close();
					break;
				case glMainMenu::Play:
					gameState = GAME_STATE::GAMEPLAY;
					break;
			}
		case GAME_STATE::GAMEPLAY:
			if(!isPlaying){
				musicObject.StopAll();
				musicObject.MusicLevel1.play();
				isPlaying = true;
			}

			graphics.setView(player1View);

			// for parallax-scrolling
			
			pos = gBoard.getTileManager().getMapHeight() - backgroundTexture.getSize().y * 6 - 0.8 * (gBoard.getTileManager().getMapHeight() - player1View.getCenter().y - 384.0f);

			for (int i = 0; i < 6; ++i)
			{
				backgroundSprite.setPosition(0, pos + i * backgroundTexture.getSize().y);
				graphics.draw(backgroundSprite);
			}
			
			gBoard.Draw(graphics, player1View.getCenter(), player1View.getSize(), true,heroLeft.position,heroRight.position);
			
			heroLeft.Draw(graphics);
			
			gProgressBar.DrawLava(graphics, true);

			for (int i = 0; i < bulletsVecLeft.size(); ++i) {
				bulletsVecLeft.at(i).Draw(graphics);
			}

			graphics.setView(player2View);

			// for parallax-scrolling

			pos = gBoard.getTileManager().getMapHeight() - backgroundTexture.getSize().y * 6 - 0.8 * (gBoard.getTileManager().getMapHeight() - player2View.getCenter().y - 384.0f);

			for (int i = 0; i < 6; ++i)
			{
				backgroundSprite.setPosition(0, pos + i * backgroundTexture.getSize().y);
				graphics.draw(backgroundSprite);
			}
			
			gBoard.Draw(graphics, player2View.getCenter(), player2View.getSize(), false,heroLeft.position,heroRight.position);
			
			heroRight.Draw(graphics);
			
			gProgressBar.DrawLava(graphics, false);

			for (int i = 0; i < bulletsVecRight.size(); ++i) {
				bulletsVecRight.at(i).Draw(graphics);
			}

			graphics.setView(graphics.getDefaultView());
			gProgressBar.Draw(graphics);

			score.Draw(graphics);

			graphics.setView(player1View);

			for (int i = 0; i < bulletsVecLeft.size(); ++i) {
				bulletsVecLeft.at(i).DrawWarning(graphics, player1View.getCenter().y + 384);
			}

			graphics.setView(player2View);

			for (int i = 0; i < bulletsVecRight.size(); ++i) {
				bulletsVecRight.at(i).DrawWarning(graphics, player2View.getCenter().y + 384);
			}

			break;
		case GAME_STATE::WIN:
			if(!isWin){
				musicObject.StopAll();
				isWin = true;
			}
			break;
		case GAME_STATE::GAMEOVER:
			if(!isGameOver){
				musicObject.StopAll();
				musicObject.MusicGameOver.play();
				isGameOver = true;
			}
			DrawGameOver(graphics);
			break;
	}
	
}

void glGame::DrawGameOver(sf::RenderWindow& graphics)
{
	gameOverBackground.loadFromFile(concat(glSettings::ASSETS_PATH, "gameOver.jpg"));
	gameOverBackgroundSprite.setTexture(gameOverBackground);
	gameOverBackgroundSprite.setOrigin(gameOverBackground.getSize().x/2., gameOverBackground.getSize().y/2.);
	gameOverBackgroundSprite.setPosition(graphics.getSize().x/2., graphics.getSize().y/2.);

	sf::View view(sf::FloatRect(0, 0, graphics.getSize().x, graphics.getSize().y));
	graphics.setView(view);

	graphics.clear(sf::Color(0,0,0));
	graphics.draw(gameOverBackgroundSprite);
}

void glGame::HandleEvent(sf::Event event)
{
	if(event.type == event.KeyReleased)
	{
		if(event.key.code == sf::Keyboard::E)
		{
			float x = heroLeft.position.x+heroLeft.getWidth()/2;
			float y = heroLeft.position.y+heroLeft.getHeight()/2;
			glTiledLoader tileManager = gBoard.getTileManager();
			int row, column;
			tileManager.getTileCoords(x, y, heroLeft.playerId, row, column);

			glTiled& tile = gBoard.getTileManager().getTile(row, column);
			
			if(tile.type >= OBJECTS_MIN)
			{
				tile.press();	
				if(tile.readyToExecAssociatedAction)
				{
					gBoard.getTileManager().runActionOnAssociated(row, column);
					gBoard.getTileManager().runActionOnAssociatedLasers(row, column);
				} else 
				{
					musicObject.PlaySound("press" + to_string(rand()%4+1));
				}
			}
		}

		if (event.key.code == sf::Keyboard::RControl)
		{
			float x = heroRight.position.x+heroRight.getWidth()/2;
			float y = heroRight.position.y+heroRight.getHeight()/2;
			glTiledLoader tileManager = gBoard.getTileManager();
			int row, column;
			tileManager.getTileCoords(x, y, heroRight.playerId, row, column);

			glTiled& tile = gBoard.getTileManager().getTile(row, column);
			
			if(tile.type >= OBJECTS_MIN)
			{
				tile.press();	
				if(tile.readyToExecAssociatedAction)
				{
					gBoard.getTileManager().runActionOnAssociated(row, column);
					gBoard.getTileManager().runActionOnAssociatedLasers(row, column);
				} else 
				{
					musicObject.PlaySound("press" + to_string(rand()%4+1));
				}
			}
		}
	}
}

void glGame::CheckColisions()
{
	
	for (int i = 0; i < bulletsVecLeft.size(); ++i)
	{
		sf::Vector2f bulletPosition = bulletsVecLeft.at(i).bulletSprite.getPosition();
		sf::Vector2u bulletSize = bulletTexture.getSize();

		if (!bulletsVecLeft.at(i).mDying)
		{
			if (bulletPosition.x + bulletSize.x > heroLeft.position.x && bulletPosition.x < heroLeft.position.x + heroLeft.getWidth())
				if (bulletPosition.y + bulletSize.y > heroLeft.position.y && bulletPosition.y < heroLeft.position.y + heroLeft.getHeight())
				{
					heroLeft.death = true;
					bulletsVecLeft.at(i).mDying = true;
				}
		}
	}

	for (int i = 0; i < bulletsVecRight.size(); ++i)
	{
		sf::Vector2f bulletPosition = bulletsVecRight.at(i).bulletSprite.getPosition();
		sf::Vector2u bulletSize = bulletTexture.getSize();

		if (!bulletsVecRight.at(i).mDying)
		{
			if (bulletPosition.x + bulletSize.x > heroRight.position.x && bulletPosition.x < heroRight.position.x + heroRight.getWidth())
				if (bulletPosition.y + bulletSize.y > heroRight.position.y && bulletPosition.y < heroRight.position.y + heroRight.getHeight())
				{
					heroRight.death = true;
					bulletsVecRight.at(i).mDying = true;
				}
		}
	}
								
}
