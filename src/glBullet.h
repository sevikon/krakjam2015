#pragma once
#include <SFML/Graphics.hpp>

class glBullet
{	
public:
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	float mVelocity;
	bool mDying;
	bool mFallen;
	void Init(float x, float y, float velocity);
	void Update();
	void Draw(sf::RenderWindow& graphics);
};