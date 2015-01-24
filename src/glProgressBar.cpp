#include "glProgressBar.h"
#include <stdio.h>
#include "glUtils.h"
#include "glSettings.h"
#include <iostream>     // std::cout
#include <sstream>
#include <string>
#include <math.h>       /* floor */

void glProgressBar::Load()
{
	backgroundTexture[0].loadFromFile(concat(glSettings::ASSETS_PATH, "pb0.png"));
	backgroundSprite[0].setTexture(backgroundTexture[0]);

	backgroundTexture[1].loadFromFile(concat(glSettings::ASSETS_PATH, "pb-z1.png"));
	backgroundSprite[1].setTexture(backgroundTexture[1]);

	backgroundTexture[2].loadFromFile(concat(glSettings::ASSETS_PATH, "pb-z2.png"));
	backgroundSprite[2].setTexture(backgroundTexture[2]);

	pbTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "pb-bar.png"));
	pbTexture.setRepeated(true);
}

void glProgressBar::Init()
{
	lava=6400-24;
	player1=6400-24;
	player2=6400-24;
}

void glProgressBar::Update(float play1, float play2)
{
	player1=play1;
	player2=play2;
}

void glProgressBar::Draw(sf::RenderWindow& graphics)
{	
	// define a 120x50 rectangle

	lava-=1.3;
	player1-=2.6;
	player2-=1.8;
	if (lava<0){
		lava=0;
	}
	if (player1<0){
		player1=0;
	}
	if (player2<0){
		player2=0;
	}

	backgroundSprite[0].setPosition(620,0);
	graphics.draw(backgroundSprite[0]);

	float actual = ((1-(lava/6400))*754);
	float actualPlayer1 = ((1-(player1/6400))*754);
	float actualPlayer2 = ((1-(player2/6400))*754);

	sf::RectangleShape rectangle(sf::Vector2f(13, actual));
	rectangle.setTexture(&pbTexture,true); // texture is a sf::Texture
	rectangle.setTextureRect(sf::IntRect(0,0,50,actual));
	rectangle.setPosition(639,763-actual);
	graphics.draw(rectangle);

	backgroundSprite[1].setPosition(592,763-actualPlayer1);
	graphics.draw(backgroundSprite[1]);

	backgroundSprite[2].setPosition(660,763-actualPlayer2);
	graphics.draw(backgroundSprite[2]);
}