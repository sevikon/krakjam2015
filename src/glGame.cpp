#include "glGame.h"
#include <stdio.h>
#include "glUtils.h"
#include "glSettings.h"
#include <iostream>

void glGame::Load()
{
	backgroundTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "bg.png"));
	backgroundSprite.setTexture(backgroundTexture);
}

void glGame::Init(sf::RenderWindow& window)
{
	printf("-----------------------------------------------------\n");
	printf("Zaczynamy nowa gre.\n");
	printf("-----------------------------------------------------\n");

	player1View.setSize(sf::Vector2f(window.getSize().x/2.f, window.getSize().y/1.f));
	player2View.setSize(sf::Vector2f(window.getSize().x/2.f, window.getSize().y)/1.f);
	player1View.setCenter(player1View.getSize().x/2, player1View.getSize().y/2);
	player2View.setCenter(player2View.getSize().x/2, player2View.getSize().y/2);

	// player 1 (left side of the screen)
	player1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	// player 2 (right side of the screen)
	player2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));

	cout << "Viewport for player1 center: " <<  player1View.getCenter().x << ", " << player1View.getCenter().y << endl;
}

void glGame::Update()
{	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player1View.move(0.f, 0.05f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player1View.move(0.f, -0.05f);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player2View.move(0.f, 0.05f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player2View.move(0.f, -0.05f);
	}
	
}

void glGame::Draw(sf::RenderWindow& graphics)
{		
	graphics.setView(graphics.getDefaultView());
	seMainMenu::MenuResult result = mainMenu.Show(graphics,graphics.getSize().x, graphics.getSize().y);
	switch(result)
	{
		case seMainMenu::Exit:
			graphics.close();
			break;
		case seMainMenu::Play:
			graphics.setView(player1View);
			graphics.draw(backgroundSprite);
			graphics.setView(player2View);
			graphics.draw(backgroundSprite);
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