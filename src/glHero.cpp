#include <string>
#include <cstring>

#include "glHero.h"
#include "glSettings.h"
#include "glUtils.h"

using namespace std;

// PARAMS
// how many frames for particular animations

const int glHero::walkingFrames = 6;
const int glHero::climbingFrames = 6;
const float glHero::frameDuration = 0.3f;
const float glHero::climbingSpeed = 20.0f;
const float glHero::walkingSpeed = 30.0f;
const float glHero::fallingSpeed = 40.0f;

// how much time passes between frames

const float DELTA = 1.0f / 60.0f;

void glHero::Load(int _side)
{

	side = _side;

	string tmp;

	sprintf((char*)tmp.c_str(), "%d", _side);

	string str = tmp.c_str();

	for (int a = 0; a < walkingFrames; a++) {

		string actual;
		sprintf((char*)actual.c_str(), "%d", a);
		string actualny = actual.c_str();

		imageWalkingLeft[a].loadFromFile(concat(glSettings::ASSETS_PATH, "hero" + str + "_left_" + actualny + ".png"));
		imageWalkingRight[a].loadFromFile(concat(glSettings::ASSETS_PATH, "hero" + str + "_right_" + actualny + ".png"));

	}

	for (int a = 0; a < climbingFrames; a++) {

		string actual;
		sprintf((char*)actual.c_str(), "%d", a);
		string actualny = actual.c_str();

		imageWalkingRight[a].loadFromFile(concat(glSettings::ASSETS_PATH, "hero" + str + "_climb_" + actualny + ".png"));

	}

	imageIdle.loadFromFile(concat(glSettings::ASSETS_PATH, "hero_front.png"));

}

void glHero::Init()
{

	currentFrame = 0;
	lastEvent = NONE;

}

void glHero::Update(event _event)
{

	// zapisanie stanu, na potrzeby klasy nadrzednej

	lastEvent = _event;

	// ruch

	if (_event | CLIMBUP)
	{
		position.y -= climbingSpeed * DELTA;
	}

	if (_event | CLIMBDOWN)
	{
		position.y += climbingSpeed * DELTA;
	}

	if (_event | RIGHT)
	{
		position.x += walkingSpeed * DELTA;
	}

	if (_event | LEFT)
	{
		position.x -= walkingSpeed * DELTA;
	}

	if (_event | FALL)
	{
		position.y += fallingSpeed * DELTA;
	}

	if (_event | NONE)
	{
		animationTimer = 0;
		currentFrame;
	}
	
	// animacje

	if (_event | CLIMBUP)
	{
		animationTimer += DELTA;

		if (animationTimer > frameDuration)
			currentFrame++;

		if (currentFrame >= climbingFrames)
			currentFrame = 0;

		sprite.setTexture(imageClimbingUp[currentFrame]);
	}

	if (_event | CLIMBUP)
	{
		animationTimer += DELTA;

		if (animationTimer > frameDuration)
			currentFrame++;

		if (currentFrame >= climbingFrames)
			currentFrame = 0;

		sprite.setTexture(imageClimbingDown[currentFrame]);
	}

	if (_event | RIGHT)
	{
		if (_event | FALL)
		{
			sprite.setTexture(imageWalkingRight[3]);
		}
		else
		{
			animationTimer += DELTA;

			if (animationTimer > frameDuration)
				currentFrame++;

			if (currentFrame >= walkingFrames)
				currentFrame = 0;

			sprite.setTexture(imageWalkingRight[currentFrame]);
		}
	}

	if (_event | LEFT)
	{
		if (_event | FALL)
		{
			sprite.setTexture(imageWalkingLeft[3]);
		}
		else
		{
			animationTimer += DELTA;

			if (animationTimer > frameDuration)
				currentFrame++;

			if (currentFrame >= walkingFrames)
				currentFrame = 0;

			sprite.setTexture(imageWalkingLeft[currentFrame]);
		}
	}
	
}

void glHero::Draw(sf::RenderWindow& graphics)
{

	sprite.setPosition(position);
	graphics.draw(sprite);

}