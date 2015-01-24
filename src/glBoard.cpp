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
}

void glBoard::Draw(sf::RenderWindow& graphics,sf::Vector2f pos,sf::Vector2f size,glTiledLoader &gTiledLoader,bool left)
{		
	cout<<"saf"<<endl;
	int beginX;
	int endX;
	if (left){
		beginX=0;
		endX=10;
	}else{
		beginX=10;
		endX=20;
	};
	int tiledSize =64;
	int beginY= floor((pos.y-384)/tiledSize);
	int endY= floor(((pos.y-384+size.y))/tiledSize)+1;
	int act=0;
	//graphics.setView(graphics.getDefaultView());
	for (int a=beginX;a<endX;a++){
		for (int b=beginY;b<endY;b++){
			if (act>=0 && act<=10 && a>=0 && b>=0 && b<100 && a<20){
				act = gTiledLoader.getValue(b,a);
				if (left)
					backgroundSprite[act].setPosition(a*tiledSize,(b)*tiledSize);
				else
					backgroundSprite[act].setPosition((a-10)*tiledSize,(b)*tiledSize);
				graphics.draw(backgroundSprite[act]);
			}
			
		}
	}
}