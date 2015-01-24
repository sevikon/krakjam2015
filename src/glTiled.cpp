#include "glTiled.h"
#include "glSettings.h"
#include <iostream>
#include <fstream>
#include <iostream>     // std::cout
#include <sstream>
#include <string>
#include <vector>

using namespace std;

glTiled::glTiled(int type){
	this->type = type;
	this->active = false;
	this->used=false;
	this->pressed=false;
	this->framesPressed=false;
	this->framesActive=false;
	this->opacity=1;
}

float glTiled::getLowerOpacity(){
	opacity -= 0.001f;
	if (opacity < 0.3){
		opacity = 0.3;
	}
	return opacity;
}

bool glTiled::isActive()
{
	return active;
}

bool glTiled::isPressed()
{
	return pressed;
}

bool glTiled::isUsed()
{
	return used;
}

void glTiled::Init(sf::RenderWindow& window) {
	
}

void glTiled::Update() {
	if (framesPressed>0){
		framesPressed--;
	}
	if (framesPressed>0 && framesPressed<5){
		framesPressed=0;
		pressed=false;
	}

	if (framesActive>0){
		framesActive--;
	}
	if (framesActive>0 && framesActive<5){
		framesActive=0;
		active=false;
	}
}

void glTiled::setPressed(int framesPressed) {
	pressed=true;
	framesPressed=30+5;
}

void glTiled::runActionOnAssociated(){
	if (type>=OBJECTS_MIN && type%2==0) (*associated).setDefinitelyActive();
}

void glTiled::setActive(int framesPressed) {
	if (type>=OBJECTS_MIN){
		active=true;
		framesPressed=30+5;
	}
}

void glTiled::setDefinitelyActive() {
	if (type>=OBJECTS_MIN){
		if (type%2!=0){
			active=true;
			framesPressed=0;
		}
		this->runActionOnAssociated();
	}
}

void glTiled::setUsed() {
	used=true;
}