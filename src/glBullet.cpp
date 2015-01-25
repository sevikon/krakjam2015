#include "glBullet.h"
#include "glSettings.h"
#include "glUtils.h"

void glBullet::Init(float x, float y, float velocity)
{
	bulletTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "bullet.png"));
	bulletSprite.setOrigin(bulletTexture.getSize().x/2., bulletTexture.getSize().y/2.);

	bulletSprite.setPosition(x,y);
	mVelocity = velocity;
	mDying = false;
}

void glBullet::Update()
{
	bulletSprite.setTexture(bulletTexture);

	if(!mDying)
	{
		float x = bulletSprite.getPosition().x;
		float y = bulletSprite.getPosition().y;
		bulletSprite.setPosition(x+mVelocity,y);
	}

	if (bulletSprite.getPosition().x < -50){
		bulletSprite.setPosition(-50,bulletSprite.getPosition().y);
		mDying = true;
	}
	if (bulletSprite.getPosition().x > 2000){
		bulletSprite.setPosition(2000,bulletSprite.getPosition().y);
		mDying = true;
	}
}

void glBullet::Draw(sf::RenderWindow& graphics)
{		
	graphics.draw(bulletSprite);
}