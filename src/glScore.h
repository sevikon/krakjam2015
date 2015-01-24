#pragma once

#include "SFML\Graphics.hpp"

class glScore
{

	int mCurrentScore;
	sf::Texture mDigitsImage;
	sf::Texture mScoreImage;
	sf::Texture mYears;
	sf::Texture mMonths;

	sf::Sprite mDigits[10];
	sf::Sprite mScore;
	sf::Sprite mYearsSprite;
	sf::Sprite mMonthsSprite;

	float leftBorder;
	float topPos;
	float fAngle; // kat

	public:

	glScore(void);
	~glScore(void);

	void Load();
	void Init(int cScore);
	void Step();
	void Draw(sf::RenderWindow& graphics);
	void SetCurrentScore(int currentScore);
	int GetScore();

};
