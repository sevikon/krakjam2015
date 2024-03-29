#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

#include "glHero.h"
#include "glSettings.h"
#include "glUtils.h"

using namespace std;

// PARAMS
// how many frames for particular animations

const int glHero::leftWalkingFrames = 4;
const int glHero::rightWalkingFrames = 5;
const int glHero::climbingFrames = 1;
const float glHero::frameDuration = 0.1f;
const float glHero::climbingSpeed = 180.0f;
const float glHero::walkingSpeed = 220.0f;
const float glHero::fallingSpeed = 250.0f;

// how much time passes between frames

const float DELTA = 1.0f / 60.0f;

void glHero::Load(int _side)
{

	walkingFrames = (_side == 0 ? leftWalkingFrames : rightWalkingFrames);

	side = _side;

	ostringstream oss;

	for (int a = 0; a < walkingFrames; a++) {

		oss.str(string());
		oss.clear();
		oss << "hero" << side + 1 << "_left_" << a << ".png";
		imageWalkingLeft[a].loadFromFile(concat(glSettings::ASSETS_PATH, oss.str()));

		oss.str(string());
		oss.clear();
		oss << "hero" << side + 1 << "_right_" << a << ".png";
		imageWalkingRight[a].loadFromFile(concat(glSettings::ASSETS_PATH, oss.str()));

	}

	for (int a = 0; a < climbingFrames; a++) {

		oss.str(string());
		oss.clear();
		oss << "hero" << side + 1 << "_up_" << a << ".png";
		imageClimbingUp[a].loadFromFile(concat(glSettings::ASSETS_PATH, oss.str()));

		oss.str(string());
		oss.clear();
		oss << "hero" << side + 1 << "_down_" << a << ".png";
		imageClimbingDown[a].loadFromFile(concat(glSettings::ASSETS_PATH, oss.str()));

	}

}

void glHero::Init(float x, float y, sf::View View, glHero::PLAYER _playerId)
{

	position.x = x;
	position.y = y;
	playerId = _playerId;

	currentFrame = 0;
	lastEvent = NONE;

	playerView = View;
	death = false;

	opacity = 1.0f;

	if (side == 0)
	{
		sprite.setTexture(imageWalkingRight[0]);
	}

	if (side == 1)
	{
		sprite.setTexture(imageWalkingLeft[0]);
	}

}

void glHero::Update(event _event)
{

	// zapisanie stanu, na potrzeby klasy nadrzednej

	lastEvent = _event;

	// ruch

	if (_event & CLIMBUP)
	{
		position.y -= climbingSpeed * DELTA;
	}

	if (_event & CLIMBDOWN)
	{
		position.y += climbingSpeed * DELTA;
	}

	if (_event & RIGHT)
	{
		position.x += walkingSpeed * DELTA;
	}

	if (_event & LEFT)
	{
		position.x -= walkingSpeed * DELTA;
	}

	if (_event & FALL)
	{
		position.y += fallingSpeed * DELTA;
	}

	if (_event & NONE)
	{
		animationTimer = 0;
		currentFrame;
	}

	if (_event & RIGHTBORDER){
			position.x = playerView.getSize().x  - getWidth(); 
	}
	if (_event & LEFTBORDER){
			position.x = 0; 
	}
	
	// animacje

	if (_event & CLIMBUP)
	{
		animationTimer += DELTA;

		if (animationTimer > frameDuration)
		{
			currentFrame++;
			animationTimer = 0;
		}

		if (currentFrame >= climbingFrames)
			currentFrame = 0;

		sprite.setTexture(imageClimbingUp[currentFrame]);
	}

	if (_event & CLIMBDOWN)
	{
		animationTimer += DELTA;

		if (animationTimer > frameDuration)
		{
			currentFrame++;
			animationTimer = 0;
		}

		if (currentFrame >= climbingFrames)
			currentFrame = 0;

		sprite.setTexture(imageClimbingDown[currentFrame]);
	}

	if (_event & RIGHT)
	{
		if (_event & FALL)
		{
			sprite.setTexture(imageWalkingRight[0]);
		}
		else
		{
			animationTimer += DELTA;

			if (animationTimer > frameDuration)
			{
				currentFrame++;
				animationTimer = 0;
			}

			if (currentFrame >= walkingFrames)
				currentFrame = 0;

			sprite.setTexture(imageWalkingRight[currentFrame]);
		}
	}

	if (_event & LEFT)
	{
		if (_event & FALL)
		{
			sprite.setTexture(imageWalkingLeft[0]);
		}
		else
		{
			animationTimer += DELTA;

			if (animationTimer > frameDuration)
			{
				currentFrame++;
				animationTimer = 0;
			}

			if (currentFrame >= walkingFrames)
				currentFrame = 0;

			sprite.setTexture(imageWalkingLeft[currentFrame]);
		}
	}

	// dying

	if (death == 1)
	{
		opacity -= 0.3f * DELTA;
		
		if (opacity < 0)
			opacity = 0;
	}
}

void glHero::UpdateReverse(event _event)
{
	if (_event & FALL)
	{
		position.y -= fallingSpeed * DELTA;
	}
	if (_event & RIGHT)
	{
		position.x -= walkingSpeed * DELTA;
	}
	if (_event & LEFT)
	{
		position.x += walkingSpeed * DELTA;
	}
	if (_event & CLIMBDOWN)
	{
		position.y -= climbingSpeed * DELTA;
	}
}

void glHero::Draw(sf::RenderWindow& graphics)
{
	sprite.setColor(sf::Color(255, 255 * opacity, 255 * opacity, opacity * 255));
	sprite.setPosition(position + sf::Vector2f(0,4.0f));
	graphics.draw(sprite);
	sprite.setPosition(position);
}

int glHero::getWidth()
{
	return imageWalkingLeft[0].getSize().x;
}

int glHero::getHeight()
{
	return imageWalkingLeft[0].getSize().y;
}