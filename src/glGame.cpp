#include "glGame.h"
#include <stdio.h>
#include "glUtils.h"
#include "glSettings.h"
#include <iostream>

void glGame::Load()
{
	backgroundTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "back1.png"));
	backgroundSprite.setTexture(backgroundTexture);

	heroLeft.Load(0);
	heroRight.Load(1);

	gBoard.Load();
}

void glGame::Init(sf::RenderWindow& window)
{

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

	heroLeft.Init(100, gBoard.getTileManager().getMapHeight() - 64 - heroLeft.getHeight());
	heroRight.Init(500, gBoard.getTileManager().getMapHeight() - 64 - heroRight.getHeight());

	// gameState = GAME_STATE::MENU;
	gameState = GAME_STATE::GAMEPLAY;
}

void glGame::Update()
{	

	// player 1 movement

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		heroLeft.Update(glHero::LEFT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		heroLeft.Update(glHero::CLIMBUP);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		heroLeft.Update(glHero::RIGHT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		heroLeft.Update(glHero::CLIMBDOWN);
	}

	// player 2 movement

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		heroRight.Update(glHero::LEFT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		heroRight.Update(glHero::CLIMBUP);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		heroRight.Update(glHero::RIGHT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		heroRight.Update(glHero::CLIMBDOWN);
	}
	
	int row;
	int column;

	heroLeft.Update(glHero::FALL);
	if(gBoard.getTileManager().intersectsWithWall(heroLeft.getSpirte()))
		heroLeft.UpdateReverse(glHero::FALL);

	heroRight.Update(glHero::FALL);
	if(gBoard.getTileManager().intersectsWithWall(heroRight.getSpirte()))
		heroRight.UpdateReverse(glHero::FALL);
}

void glGame::Draw(sf::RenderWindow& graphics)
{		
	graphics.setView(graphics.getDefaultView());

	switch(gameState)
	{
		case GAME_STATE::MENU:
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

			graphics.setView(player1View);
			gBoard.Draw(graphics, player1View.getCenter(), player1View.getSize(), true);
			heroLeft.Draw(graphics);

			graphics.setView(player2View);
			gBoard.Draw(graphics, player2View.getCenter(), player2View.getSize(), false);
			heroRight.Draw(graphics);

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