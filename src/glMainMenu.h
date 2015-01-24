#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>

class glMainMenu
{

public:
	enum MenuResult { Nothing, Exit, Play };	
	
	struct MenuItem
		{
		public:
			sf::Rect<int> rect;
			MenuResult action;
		};

	sf::Event event;
	MenuResult Show(sf::RenderWindow& window, float viewWidth, float viewHeight);
	void Load();

	sf::Texture mBackgroundMenu;
	sf::Sprite mBackgroundSpriteMenu;

	sf::Texture mStart, mExit;
	sf::Sprite mStartSprite, mExitSprite;

	//heroes
	sf::Sprite mActiveSprite1;
	sf::Texture mBackFront1;
	sf::Sprite mActiveSprite2;
	sf::Texture mBackFront2;


private:
	MenuResult GetMenuResponse(sf::RenderWindow& window, float viewWidth, float viewHeight);
	MenuResult HandleClick(int x, int y,sf::RenderWindow& window, float viewWidth, float viewHeight);
	std::list<MenuItem> _menuItems;
};