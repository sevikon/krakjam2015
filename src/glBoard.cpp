#include "glBoard.h"
#include <stdio.h>
#include "glUtils.h"
#include "glSettings.h"
#include <iostream>     // std::cout
#include <sstream>
#include <string>
#include <math.h>       /* floor */

void glBoard::Load()
{
	for (int a=0;a<SPRITES;a++){
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
	mTileManager.Update();
}

glTiledLoader& glBoard::getTileManager()
{
	return this->mTileManager;
}

void glBoard::Draw(sf::RenderWindow& graphics,sf::Vector2f pos,sf::Vector2f size,bool left)
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

	//graphics.setView(graphics.getDefaultView());
	for (int a=beginX;a<endX;a++) {
		for (int b=beginY;b<endY;b++) {

			if (a>=0 && b>=0 && b<100 && a<20) {
				act = mTileManager.getValue(b, a);
				int x,y;
				mTileManager.getTileCoords(b,a,x,y);
				if(act>=2 && act<=10 && !mTileManager.isActive(x,y)){
					if (left)
						backgroundSprite[act].setPosition(a*tiledSize,(b)*tiledSize);
					else
						backgroundSprite[act].setPosition((a-10)*tiledSize,(b)*tiledSize);
					graphics.draw(backgroundSprite[act]);
				}
			}
			
		}
	}
}