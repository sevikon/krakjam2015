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
	backgroundTexture[0].loadFromFile(concat(glSettings::ASSETS_PATH, "progress-bar.png"));
	backgroundSprite[0].setTexture(backgroundTexture[0]);

	backgroundTexture[1].loadFromFile(concat(glSettings::ASSETS_PATH, "pb-z1.png"));
	backgroundSprite[1].setTexture(backgroundTexture[1]);

	backgroundTexture[2].loadFromFile(concat(glSettings::ASSETS_PATH, "pb-z2.png"));
	backgroundSprite[2].setTexture(backgroundTexture[2]);

	backgroundTexture[3].loadFromFile(concat(glSettings::ASSETS_PATH, "death-1.png"));
	backgroundSprite[3].setTexture(backgroundTexture[3]);

	backgroundTexture[4].loadFromFile(concat(glSettings::ASSETS_PATH, "death-2.png"));
	backgroundSprite[4].setTexture(backgroundTexture[4]);

	backgroundTexture[5].loadFromFile(concat(glSettings::ASSETS_PATH, "death-3.png"));
	backgroundSprite[5].setTexture(backgroundTexture[5]);

	backgroundTexture[6].loadFromFile(concat(glSettings::ASSETS_PATH, "death-4.png"));
	backgroundSprite[6].setTexture(backgroundTexture[6]);

	pbTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "progress-level.png"));
	pbSprite.setTexture(pbTexture);

}

void glProgressBar::Init()
{
	lava=6400-50;
	player1=6400-24;
	player2=6400-24;

	timer.restart();
}

void glProgressBar::Update(float play1, float play2)
{
	player1=play1;
	player2=play2;
}

void glProgressBar::Draw(sf::RenderWindow& graphics)
{	
	// define a 120x50 rectangle

	if(timer.getElapsedTime().asSeconds() > 3){
		lava-=0.004+0.0004*timer.getElapsedTime().asSeconds();}

	if (lava<0){
		lava=0;}

	backgroundSprite[0].setPosition(625,0);
	graphics.draw(backgroundSprite[0]);

	float actual = ((1-(lava/6400))*754);
	float actualPlayer1 = ((1-(player1/6400))*754);
	float actualPlayer2 = ((1-(player2/6400))*754);

	if (lava-player1>180 || lava-player2>180 ){
		lava-=0.061;
	}else if (lava-player1>300 || lava-player2>300 ){
		lava-=0.074;
	}else if (lava-player1>400 || lava-player2>400 ){
		lava-=0.104;
	}else if (lava-player1>500 || lava-player2>500 ){
		lava-=0.167;
	}else if (lava-player1>600 || lava-player2>600 ){
		lava-=0.7;
	}


	pbSprite.setPosition(626,763-actual);
	graphics.draw(pbSprite);

	backgroundSprite[1].setPosition(592,763-actualPlayer1);
	graphics.draw(backgroundSprite[1]);

	backgroundSprite[2].setPosition(660,763-actualPlayer2);
	graphics.draw(backgroundSprite[2]);
}

void glProgressBar::DrawLava(sf::RenderWindow& graphics,bool left){
	
	backgroundSprite[3].setScale(sf::Vector2f(1.5f, 1.f));
	backgroundSprite[3].setPosition(8*std::sin(0.25*timer.getElapsedTime().asSeconds()),lava+5*std::sin(timer.getElapsedTime().asSeconds()));
	graphics.draw(backgroundSprite[3]);

	backgroundSprite[4].setColor(sf::Color(255, 255, 255, (0.25*std::sin(4*timer.getElapsedTime().asSeconds()+0.49)+0.75 ) * 255));
	backgroundSprite[4].setPosition(3*std::sin(timer.getElapsedTime().asSeconds()+0.75),lava+5*std::sin(timer.getElapsedTime().asSeconds()));
	graphics.draw(backgroundSprite[4]);

	backgroundSprite[5].setColor(sf::Color(255, 255, 255, (0.25*std::sin(3*timer.getElapsedTime().asSeconds()-0.51)+0.75 ) * 255));
	backgroundSprite[5].setPosition(2*std::sin(timer.getElapsedTime().asSeconds()+0.5),lava+5*std::sin(timer.getElapsedTime().asSeconds()));
	graphics.draw(backgroundSprite[5]);

	backgroundSprite[6].setColor(sf::Color(255, 255, 255, (0.3*std::sin(2*timer.getElapsedTime().asSeconds()+0.51)+0.3 ) * 255));
	backgroundSprite[6].setPosition(10*std::sin(0.1*timer.getElapsedTime().asSeconds()-0.5),30+lava+20*std::sin(timer.getElapsedTime().asSeconds()));
	graphics.draw(backgroundSprite[6]);

}