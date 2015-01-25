#pragma once
#include <SFML/Graphics.hpp>

class glBullet
{	
public:
	static sf::Texture bulletTexture;

	sf::Sprite bulletSprite;
	float mVelocity;
	bool mDying;

	static void Load();
	void Init(float x, float y, float velocity);
	void Update();
	void Draw(sf::RenderWindow& graphics);
};