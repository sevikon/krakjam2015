#pragma once
#include <SFML/Graphics.hpp>

class glBullet
{	
public:

	sf::Texture *bulletTexture;
	sf::Sprite bulletSprite;

	const static float acceleration;

	float mVelocity;
	float mOpacity;
	bool mDying;

	static void Load();
	void Init(int bottomEdge, sf::Texture * texture);
	void Update();
	void Draw(sf::RenderWindow& graphics);
};