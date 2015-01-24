#pragma once
#include "SFML\Graphics.hpp"

class glTiled
{
private:
	
public: 
	int posX;
	int posY;
	bool isActive;
	int type;
	void Load();
	void Init(sf::RenderWindow& window);
};