#include "glBullet.h"
#include "glSettings.h"
#include "glUtils.h"

// how much time passes between frames

const float DELTA = 1.0f / 60.0f;
const float glBullet::acceleration = 1500.0f;

void glBullet::Init(int bottomEdge, sf::Texture * texture, sf::Texture * warning)
{
	bulletTexture = texture;

	bulletSprite.setPosition(20 + rand() % 600 - bulletTexture->getSize().x, bottomEdge + 10);

	bulletSprite.setTexture(*bulletTexture);

	mVelocity = - (rand() % 600 + 1200); // 60 - 140 px/sec
	mDying = false;

	mOpacity = 1.0f;

	mTimer = 0;

	warningTexture = warning;
	warningSprite.setTexture(*warningTexture);
	
	mPlayed = false;

}

void glBullet::Update()
{

	mTimer += DELTA;

	if(!mDying)
	{
		if (mTimer > 2.2f)
		{
			

			float x = bulletSprite.getPosition().x;
			float y = bulletSprite.getPosition().y;

			bulletSprite.setPosition(x, y + mVelocity * DELTA);
			mVelocity += acceleration * DELTA;
		}

		if (mTimer > 2.0f)
		{
			if (!mPlayed)
			{
				mPlayed = true;
				musicObject.PlaySound("bullet");
			}
		}
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

void glBullet::DrawWarning(sf::RenderWindow& graphics, int bottomEdge)
{

	warningSprite.setPosition(bulletSprite.getPosition().x - (bulletTexture->getSize().x - warningTexture->getSize().x) + (rand() % 16 - 8), bottomEdge - warningTexture->getSize().y - 30 + (rand() % 16 - 8));

	if (mTimer < 2.0f)
		graphics.draw(warningSprite);

}