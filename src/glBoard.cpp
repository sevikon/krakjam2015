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
}

void glBoard::Init(sf::RenderWindow& window)
{
	mTileManager.loadMap(1);
}

void glBoard::Update()
{

	mAngle += DELTA * 0.7f;
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

	//graphics.setView(graphics.getDefaultView());
	for (int a=beginX;a<endX;a++) {
		for (int b=beginY;b<endY;b++) {
			if (a>=0 && b>=0 && b<100 && a<20) {
				act = mTileManager.getValue(b, a);
				if (act==INVISIBLE_POSX){
					draw = true;
					p=a;
					r=b;
				}
				else if(act>=1 && act<=SPRITES && !mTileManager.isActive(b,a)){
					if (left)
						backgroundSprite[act].setPosition(a*tiledSize, (b)*tiledSize + (act >= OBJECTS_MIN && act <= OBJECTS_MAX ? 10 * sin(mAngle) - 10 : 0));
					else
						backgroundSprite[act].setPosition((a-10)*tiledSize,(b)*tiledSize);
					backgroundSprite[act].setColor(mTileManager.getColor(b,a));
					float opacity = mTileManager.getOpacity(b,a);
					if (std::abs(leftHero.y-rightHero.y)<=4*64){
						backgroundSprite[act].setColor(sf::Color(255, 255, 255,255));
					}
					graphics.draw(backgroundSprite[act]);// define a 120x50 rectangle
					backgroundSprite[act].setColor(sf::Color(255, 255, 255,255));
				}else if ((act==FREE || (act>=OBJECTS_MIN && act<=OBJECTS_MAX)) && mTileManager.isActive(b,a)){
					float opacity = mTileManager.getLowerOpacity(b,a);
					if (left)
						backgroundSprite[act].setPosition(a*tiledSize, (b)*tiledSize + (act >= OBJECTS_MIN && act <= OBJECTS_MAX ? 5 * sin(mAngle) : 0));
					else
						backgroundSprite[act].setPosition((a - 10)*tiledSize, (b)*tiledSize + (act >= OBJECTS_MIN && act <= OBJECTS_MAX ? 5 * sin(mAngle) : 0));
					backgroundSprite[act].setColor(sf::Color(255* opacity, 255, 255 * opacity, opacity * 255));
					graphics.draw(backgroundSprite[act]);
				}
			}
			
		}
	}
	if (draw){
		// define a 120x50 rectangle
	/*	sf::RectangleShape rectangle(sf::Vector2f(640, 4*64));
		rectangle.setPosition(p*tiledSize,(r-3)*tiledSize);
		rectangle.setFillColor(sf::Color(110, 110, 110, 250));
		graphics.draw(rectangle);*/
	}
}