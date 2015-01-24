#include <cstdio>
#include <iostream>

#include "glScore.h"
#include "glUtils.h"
#include "glSettings.h"

using namespace std;

glScore::glScore(void)
{
}

glScore::~glScore(void)
{
}

void glScore::Load()
{

	if (!mDigitsImage.loadFromFile(concat(glSettings::ASSETS_PATH, "numbers.png")))
		printf("B³¹d przy wczytywaniu pliku data/numbers.png");

	if (!mScoreImage.loadFromFile(concat(glSettings::ASSETS_PATH, "scoreBgnd.png")))
		printf("B³¹d przy wczytywaniu pliku data/score.png");

	if (!mYears.loadFromFile(concat(glSettings::ASSETS_PATH, "years.png")))
		printf("B³¹d przy wczytywaniu pliku data/years.png");

	mYearsSprite.setTexture(mYears);

	if (!mMonths.loadFromFile(concat(glSettings::ASSETS_PATH, "months.png")))
		printf("B³¹d przy wczytywaniu pliku data/monhts.png");

	mMonthsSprite.setTexture(mMonths);

}

void glScore::Init(int cScore)
{

	mCurrentScore = cScore;

	mScore.setTexture(mScoreImage);

	mScore.setOrigin(mScoreImage.getSize().x / 2, mScoreImage.getSize().y / 2);

	for(int w = mDigitsImage.getSize().x / 10, h = mDigitsImage.getSize().y, i = 0; i < 10; i++)
	{
		mDigits[i].setTexture(mDigitsImage);
		mDigits[i].setTextureRect(sf::IntRect(i * w, 0, w, h));
	}

}

void glScore::Step()
{
	//fAngle += ONE_FRAME_DURATION*5.0f;
	//if (fAngle > 100.0f) fAngle = 0.0f;
	//mScore.SetRotation( 10*sin(fAngle) );
}

void glScore::Draw(sf::RenderWindow& graphics)
{

	// drawing the score background

	mScore.setPosition(sf::Vector2f(mScoreImage.getSize().x / 2 + 5, 768 - mScoreImage.getSize().y / 2 - 5));

	graphics.draw(mScore);

	int years = mCurrentScore / 12;
	int months = mCurrentScore % 12;

	//drawing years and months

	std::vector<int> digYears;

	int digit;

	if (years == 0)
		digYears.push_back(0);
	else
		while (years > 0)
		{
			digit = years % 10;
			digYears.insert(digYears.begin(), digit);
			years /= 10;
		}

	std::vector<int> digMonths;

	if (months == 0)
		digMonths.push_back(0);
	else
		while (months > 0)
		{
			digit = months % 10;
			digMonths.insert(digMonths.begin(), digit);
			months /= 10;
		}


	float pos = mScore.getPosition().x - ((digYears.size() + digMonths.size() + 4) * 25) / 2 - 14;
	
	// drawing years

	for(unsigned int i = 0; i < digYears.size(); ++i)
	{
		mDigits[digYears[i]].setPosition(sf::Vector2f(float(pos + (i * (25))), mScore.getPosition().y - 30));
		graphics.draw(mDigits[digYears[i]]);
	}

	pos += 50;

	// drawing "y"

	mYearsSprite.setPosition(sf::Vector2f(pos, mScore.getPosition().y - 30));
	graphics.draw(mYearsSprite);

	pos += 50;

	// drawing months

	for (unsigned int i = 0; i < digMonths.size(); ++i)
	{
		mDigits[digMonths[i]].setPosition(sf::Vector2f(float(pos + (i * (25))), mScore.getPosition().y - 30));
		graphics.draw(mDigits[digMonths[i]]);
	}

	pos += 50;

	// drawing "m"

	mMonthsSprite.setPosition(sf::Vector2f(pos, mScore.getPosition().y - 30));
	graphics.draw(mMonthsSprite);

}

void glScore::SetCurrentScore(int currentScore)
{
	if (currentScore > mCurrentScore)
		mCurrentScore = currentScore;
}

int glScore::GetScore()
{
	return mCurrentScore;
}