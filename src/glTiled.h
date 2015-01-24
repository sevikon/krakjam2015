#pragma once
#include "SFML\Graphics.hpp"

class glTiled
{
private:
	int posX;
	int posY;
	bool active;
	bool used;
	bool pressed;
	int framesPressed;
	int framesActive;
public: 
	int type;
	int originalType;
	glTiled(int type);
	void Load();
	void Init(sf::RenderWindow& window);
	bool isActive();
	bool isPressed();
	bool isUsed();
	void Update();
	void setPressed();
	void setUsed();
	void setDefinitelyActive();
	void setPressed(int framesPressed);
	void setActive(int framesPressed);

};