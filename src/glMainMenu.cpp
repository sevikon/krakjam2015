//#include "pch.h"
#include "glMainMenu.h"
#include "glUtils.h"
#include "glSettings.h"


glMainMenu::MenuResult glMainMenu::Show(sf::RenderWindow& window, float viewWidth, float viewHeight)
{
	mBackgroundMenu.loadFromFile(concat(glSettings::ASSETS_PATH, "titlepage.png"));

	mStart.loadFromFile(concat(glSettings::ASSETS_PATH, "start.png"));
	mExit.loadFromFile(concat(glSettings::ASSETS_PATH, "exit.png"));

	mBackgroundSpriteMenu.setTexture(mBackgroundMenu);
	mBackgroundSpriteMenu.setOrigin(mBackgroundMenu.getSize().x, 0);
	mBackgroundSpriteMenu.setPosition(viewWidth, 0);

	mStartSprite.setTexture(mStart);
	mExitSprite.setTexture(mExit);
	
	mStartSprite.setOrigin(mStart.getSize().x/2 , mStart.getSize().y/2);
	mExitSprite.setOrigin(mExit.getSize().x/2 , mExit.getSize().y/2);

	mStartSprite.setPosition(viewWidth/2, viewHeight/2 - 50);
	mExitSprite.setPosition(viewWidth/2, viewHeight/2 + 120);

	sf::Vector2f v1(viewWidth/2-500.0f,viewHeight- mActiveSprite1.getLocalBounds().height -25.0f);
	mActiveSprite1.setPosition(v1);

	sf::Vector2f v2(viewWidth/2+280.0f, viewHeight- mActiveSprite2.getLocalBounds().height -265.0f);
	mActiveSprite2.setPosition(v2);

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.left = mStartSprite.getPosition().x - mStart.getSize().x/2;
	playButton.rect.height = mStart.getSize().y;
	playButton.rect.top = mStartSprite.getPosition().y - mStart.getSize().y/2;
	playButton.rect.width = mStart.getSize().x;
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = mExitSprite.getPosition().x - mExit.getSize().x/2;
	exitButton.rect.height = mExit.getSize().y;
	exitButton.rect.top = mExitSprite.getPosition().y - mExit.getSize().y/2;
	exitButton.rect.width = mExit.getSize().x;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	glMainMenu::MenuResult result;
	while(true)
	{
		/*// inicjalizacja naszzego widoku (view) i jego rozmiarów
		float windowHeight = (float)window.getSize().y;
		float viewScale = 768.0f/windowHeight;
		viewWidth = window.getSize().x*viewScale;
		viewHeight = 768;*/
		sf::View view(sf::FloatRect(0, 0, viewWidth, viewHeight));
		window.setView(view);

		window.clear(sf::Color(0,0,0));
		window.draw(mBackgroundSpriteMenu);	
		
		window.draw(mStartSprite);
		window.draw(mExitSprite);

		window.draw(mActiveSprite1);
		window.draw(mActiveSprite2);
		window.display();

		result = GetMenuResponse(window,viewWidth,viewHeight);
		if(result != Nothing)
			return result;
	}
}

glMainMenu::MenuResult glMainMenu::HandleClick(int x, int y, sf::RenderWindow& window, float viewWidth, float viewHeight)
{
	std::list<MenuItem>::iterator it;

	x = x * (viewHeight / window.getSize().y);
	y = y * (viewHeight / window.getSize().y);

	for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if( menuItemRect.top + menuItemRect.height > y 
			&& menuItemRect.top < y 
			&& menuItemRect.left < x 
			&& menuItemRect.left + menuItemRect.width > x)
			{
				return (*it).action;
			}
	}

	return Nothing;
}

glMainMenu::MenuResult  glMainMenu::GetMenuResponse(sf::RenderWindow& window, float viewWidth, float viewHeight)
{
	sf::Event menuEvent;

	while(window.pollEvent(menuEvent))
	{
		if(menuEvent.type == sf::Event::MouseButtonPressed)
		{
			return HandleClick(menuEvent.mouseButton.x,menuEvent.mouseButton.y,window,viewWidth,viewHeight);
		}
		if(menuEvent.type == sf::Event::Closed)
		{
			window.close();
			return Exit;
		}
		else
			return Nothing;
	}
}

