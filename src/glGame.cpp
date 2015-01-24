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

void glGame::Init()
{
	printf("-----------------------------------------------------\n");
	printf("Zaczynamy nowa gre.\n");
	printf("-----------------------------------------------------\n");

	// player 1 (left side of the screen)
	player1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	// player 2 (right side of the screen)
	player2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
}

void glGame::Update()
{	
}

void glGame::Draw(sf::RenderWindow& graphics)
{
	graphics.setView(player1View);
	graphics.draw(backgroundSprite);
	graphics.setView(player2View);
	graphics.draw(backgroundSprite);
}

void glGame::HandleEvent(sf::Event event)
{
	if(event.KeyPressed)
		;
}