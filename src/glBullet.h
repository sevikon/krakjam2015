#pragma once
#include <SFML/Graphics.hpp>

class glBullet
{	
public:

	sf::Texture *bulletTexture;
	sf::Sprite bulletSprite;

	sf::Texture *warningTexture;
	sf::Sprite warningSprite;

	const static float acceleration;

	float mVelocity;
	float mOpacity;
	bool mDying;
	float mTimer;

	static void Load();
	void Init(int bottomEdge, sf::Texture * texture, sf::Texture * warning);
	void Update();
	void Draw(sf::RenderWindow& graphics);
	void DrawWarning(sf::RenderWindow& graphics, int bottomEdge);

};