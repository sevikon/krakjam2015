#include "glBoard.h"
#include <stdio.h>
#include "glUtils.h"
#include "glSettings.h"
#include <iostream>     // std::cout
#include <sstream>
#include <string>
#include <cmath>


// how much time passes between frames

const float DELTA = 1.0f / 60.0f;

void glBoard::Load()
{
	for (int a=1;a<SPRITES;a++){
		ostringstream ss2;
		ss2 << a;
		string str = ss2.str();
		backgroundTexture[a].loadFromFile(concat(glSettings::ASSETS_PATH, "bg"+str+".png"));
		backgroundSprite[a].setTexture(backgroundTexture[a]);
	}

	progressBarTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "progress-bar-texture.png"));
}

void glBoard::Init(int level)
{
	mAngle = 0;
	mTileManager.loadMap(level);
}

void glBoard::Update()
{

	mAngle += DELTA * 2.f;
	if (mAngle > 360.0f) mAngle = 0.0f;

}

glTiledLoader& glBoard::getTileManager()
{
	return this->mTileManager;
}

void glBoard::Draw(sf::RenderWindow& graphics,sf::Vector2f pos,sf::Vector2f size,bool left,sf::Vector2f leftHero,sf::Vector2f rightHero)
{		
	int beginX;
	int endX;
	if (left) {
		beginX=0;
		endX=10;
	} else{
		beginX=10;
		endX=20;
	};

	int tiledSize = 64;
	int beginY= floor((pos.y-384)/tiledSize);
	int endY= floor(((pos.y-384+size.y))/tiledSize)+1;
	int act=0;
	bool draw = false; int p,r;
	int offset = 0;

	offset = (left) ? 0 : -tiledSize*10;

	//graphics.setView(graphics.getDefaultView());
	for (int a=beginX;a<endX;a++) {
		for (int b=beginY;b<endY;b++) {
			if (a>=0 && b>=0 && b<100 && a<20) {
				act = mTileManager.getValue(b, a);

				if (act==INVISIBLE_POSX) {
					draw = true;
					p=a;
					r=b;
				} else if(act>=1 && act<=SPRITES && !mTileManager.isActive(b,a)){
					backgroundSprite[act].setPosition(a*tiledSize + offset, (b)*tiledSize + (act >= OBJECTS_MIN && act <= OBJECTS_MAX ? 10 * sin(mAngle) - 10 : 0));
					backgroundSprite[act].setColor(mTileManager.getColor(b,a));
					float opacity = mTileManager.getOpacity(b,a);
					if (std::abs(leftHero.y-rightHero.y)<=4*64){
						backgroundSprite[act].setColor(sf::Color(255, 255, 255,255));
					}
					

					// draw picking progress bar
					int pressesAmount = getTileManager().getTile(b, a).amountOfPresses;
					if(pressesAmount && pressesAmount < glTiled::MAX_AMOUNT_OF_PRESSES)
					{
						DrawPressStackProgressBar(graphics, pressesAmount/(float)glTiled::MAX_AMOUNT_OF_PRESSES, a*tiledSize + offset, (b)*tiledSize);
						
					} 
					if(pressesAmount >= glTiled::MAX_AMOUNT_OF_PRESSES)
					{
						// set nice transparency effect
						backgroundSprite[act].setColor(sf::Color(255, 255, 255, 100));
					}
					
					graphics.draw(backgroundSprite[act]);// define a 120x50 rectangle
					backgroundSprite[act].setColor(sf::Color(255, 255, 255,255));

				} else if ((act==FREE || (act>=OBJECTS_MIN && act<=OBJECTS_MAX)) && mTileManager.isActive(b,a)) {

					float opacity = mTileManager.getLowerOpacity(b,a);
					if (left)
						backgroundSprite[act].setPosition(a*tiledSize, (b)*tiledSize + (act >= OBJECTS_MIN && act <= OBJECTS_MAX ? 5 * sin(mAngle) : 0));
					else
						backgroundSprite[act].setPosition((a - 10)*tiledSize, (b)*tiledSize + (act >= OBJECTS_MIN && act <= OBJECTS_MAX ? 5 * sin(mAngle) : 0));
						
					backgroundSprite[act].setColor(sf::Color(255* opacity, 255, 255 * opacity, opacity * 255));
					graphics.draw(backgroundSprite[act]);
				}

				/*
				if(act>=1 && act<=SPRITES && !mTileManager.isActive(b,a)){
					backgroundSprite[act].setPosition(a*tiledSize + offset,(b)*tiledSize);
					graphics.draw(backgroundSprite[act]);

					int pressesAmount = getTileManager().getTile(b, a).amountOfPresses;
					if(pressesAmount && pressesAmount <= glTiled::MAX_AMOUNT_OF_PRESSES)
					{
						DrawPressStackProgressBar(graphics, pressesAmount/(float)glTiled::MAX_AMOUNT_OF_PRESSES, a*tiledSize + offset, (b)*tiledSize);
					}

				} else if ((act==FREE || (act>=OBJECTS_MIN && act<=OBJECTS_MAX)) && mTileManager.isActive(b,a)){
					float opacity = mTileManager.getLowerOpacity(b,a);
					backgroundSprite[act].setPosition(a*tiledSize + offset,(b)*tiledSize);
				*/
			}
		}
	}

	if (draw) {
		// define a 120x50 rectangle
	/*	sf::RectangleShape rectangle(sf::Vector2f(640, 4*64));
		rectangle.setPosition(p*tiledSize,(r-3)*tiledSize);
		rectangle.setFillColor(sf::Color(110, 110, 110, 250));
		graphics.draw(rectangle);*/
	}

}

void glBoard::DrawPressStackProgressBar(sf::RenderWindow& graphics, float progress, float posx, float posy)
{
	sf::RectangleShape bar = sf::RectangleShape(sf::Vector2f(6.f, progress*glSettings::TILE_HEIGHT));
	bar.setTexture(&progressBarTexture);
	bar.setPosition(posx, posy + glSettings::TILE_HEIGHT - progress*glSettings::TILE_HEIGHT);
	graphics.draw(bar);
}


void glBoard::ChangeLevel(int level)
{
	mTileManager.loadMap(level);
}
