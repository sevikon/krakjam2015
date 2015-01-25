#pragma once
#include "SFML\Graphics.hpp"
#include <vector>


#define GROUND_MIN 1
#define GROUND_MAX 20
#define LADDER_MIN 21
#define LADDER_INNER 21
#define LADDER_MAX 23
#define OBJECTS_MIN 24
#define OBJECTS_MAX 31
#define LEVER_LEFT 32
#define LEVER_RIGHT 33
#define INVISIBLE_LADDER 34
#define LASER 35
#define ELEBOX 36
#define INVISIBLE_POSX 50
#define INVISIBLE_POSY 51
#define FREE 99

class glAction;
using namespace std;

class glTiled
{
private:
	
public: 
	bool active;
	bool used;
	bool pressed;
	bool readyToExecAssociatedAction;
	int framesPressed;
	int framesActive;
public: 
	sf::Color color;
	int amountOfPresses;
	int row, column;
	static const int MAX_AMOUNT_OF_PRESSES = 8;
	glTiled(int type, int row, int column);
	bool together;
	glTiled *associated;
	vector<glTiled*> actionAssociated;
	float opacity;
	int type;
	int originalType;
	
	void Load();
	void Init(sf::RenderWindow& window);
	bool isActive();
	float getLowerOpacity();
	bool isPressed();
	bool isUsed();
	void Update();
	void setPressed();
	void setUsed();
	void setDefinitelyActive();
	void setPressed(int framesPressed);
	void setActive(int framesPressed);
	void callAssociated();
	void runActionOnAssociated();
	void runActionOnAssociatedLaser();
	void runActionOnAssociatedLaserShow();
	void showLadder();
	void showLasers();
	void hideLasers();
	void press();
	void resetPresses();

protected:
	void executeAction(glAction& action);
};