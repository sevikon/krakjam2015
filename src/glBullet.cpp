#include "glBullet.h"
#include "glSettings.h"
#include "glUtils.h"

// how much time passes between frames

const float DELTA = 1.0f / 60.0f;
const float glBullet::acceleration = 5.0f;

sf::Texture glBullet::bulletTexture;

void glBullet::Load()
{
	bulletTexture.loadFromFile(concat(glSettings::ASSETS_PATH, "bullet.png"));
}

void glBullet::Init(int bottomEdge)
{

	bulletSprite.setPosition(20 + rand() % 600 - bulletTexture.getSize().x, bottomEdge + 10);

	bulletSprite.setTexture(bulletTexture);

	mVelocity = - (rand() % 80 + 60); // 60 - 140 px/sec
	mDying = false;

	mOpacity = 1.0f;

}

void glBullet::Update()
{

	if(!mDying)
	{
		float x = bulletSprite.getPosition().x;
		float y = bulletSprite.getPosition().y;
		bulletSprite.setPosition(x, y + mVelocity * DELTA);

		mVelocity += acceleration * DELTA;
	}
	else
	{
		mOpacity -= DELTA;

		if (mOpacity < 0)
			mOpacity = 0;
	}

}

void glBullet::Draw(sf::RenderWindow& graphics)
{		
	graphics.draw(bulletSprite);
}