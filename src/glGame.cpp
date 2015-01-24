#include "glGame.h"
#include <stdio.h>
#include "glUtils.h"
#include "glSettings.h"
#include <iostream>

// params

const  int glGame::bornAge = 36;
const  int glGame::level1Age = 147;
const  int glGame::level2Age = 231;
const  int glGame::level3Age = 302;
const  int glGame::level4Age = 733;
const  int glGame::level5Age = 1076;

void glGame::Load()
{

	backgroundTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "back1.png"));
	backgroundSprite.setTexture(backgroundTexture);

	gProgressBar.Load();

	heroLeft.Load(0);
	heroRight.Load(1);

	gBoard.Load();

	score.Load();

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

	// gameState = GAME_STATE::MENU;
	gameState = GAME_STATE::GAMEPLAY;
	musicObject.HandleMusic();
	isMenu = false;
	isPlaying = false;

	score.Init(0);

}

void glGame::Update()
{	
	glTiledLoader& tileManager = gBoard.getTileManager();

	if (!heroLeft.death)
	{
		// player 1 movement


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			float x = heroLeft.position.x+heroLeft.getWidth()/2;
			float y = heroLeft.position.y+heroLeft.getHeight()/2;
			int a,b;
			gBoard.getTileManager().getTileCoords(x,y,heroLeft.playerId,a,b);
			gBoard.getTileManager().runActionOnAssociated(a,b);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			heroLeft.Update(glHero::LEFT);
			if(gBoard.getTileManager().intersectsWithWallVertically(heroLeft))
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
			if(gBoard.getTileManager().intersectsWithWallVertically(heroLeft))
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			float x = heroRight.position.x+heroRight.getWidth()/2;
			float y = heroRight.position.y+heroRight.getHeight()/2;
			int a,b;
			gBoard.getTileManager().getTileCoords(x,y,heroRight.playerId,a,b);
			gBoard.getTileManager().runActionOnAssociated(a,b);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			heroRight.Update(glHero::LEFT);
			if(gBoard.getTileManager().intersectsWithWallVertically(heroRight))
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
			if(gBoard.getTileManager().intersectsWithWallVertically(heroRight))
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

	if(heroRight.position.y + heroRight.getHeight() > gProgressBar.lava){
		heroRight.death = true;}
	if(heroLeft.position.y + heroLeft.getHeight() > gProgressBar.lava){
		heroLeft.death = true;}

	// updating score

	float progress = (float(gBoard.getTileManager().getMapHeight() - player1View.getCenter().y - 384) / float(gBoard.getTileManager().getMapHeight() - 768.0f));
	
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

	switch(gameState)
	{
		case GAME_STATE::MENU:
			if(isPlaying){
				musicObject.MusicLevel1.stop();
				isPlaying = false;
			}
			if(!isMenu){	
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
			if(isMenu){
				musicObject.MusicMenu.stop();
				isMenu = false;
			}
			if(!isPlaying){
				musicObject.MusicLevel1.play();
				isPlaying = true;
			}
			graphics.setView(player1View);
			gBoard.Draw(graphics, player1View.getCenter(), player1View.getSize(), true);
			gProgressBar.DrawLava(graphics,true);
			heroLeft.Draw(graphics);

			graphics.setView(player2View);
			gBoard.Draw(graphics, player2View.getCenter(), player2View.getSize(), false);
			gProgressBar.DrawLava(graphics,false);
			heroRight.Draw(graphics);

			graphics.setView(graphics.getDefaultView());
			gProgressBar.Draw(graphics);

			score.Draw(graphics);

			break;
	}
	
}

void glGame::HandleEvent(sf::Event event)
{
	if(event.type == event.KeyPressed)
	{
		/*sf::Keyboard::Key key = event.key.code;
		if(key == sf::Keyboard::Left)
		{
		}
		else if(key == sf::Keyboard::Up)
		{
			player1View.move(0.f, 2.f);
		}
		else if(key == sf::Keyboard::Right)
		{			
		}
		else if(key == sf::Keyboard::Down)
		{
			player1View.move(0.f, -2.f);
		}
		else if(key == sf::Keyboard::A)
		{
		}
		else if(key == sf::Keyboard::W)
		{
			player2View.move(0.f, 2.f);
		}
		else if(key == sf::Keyboard::D)
		{
		}
		else if(key == sf::Keyboard::S)
		{
			player2View.move(0.f, -2.f);
		}*/
	}
}