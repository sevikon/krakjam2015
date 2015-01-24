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
#define FREE 99

class glAction;
using namespace std;

class glTiled
{
private:
	bool active;
	bool used;
	bool pressed;
	int framesPressed;
	int framesActive;
public: 
	glTiled *associated;
	vector<glTiled*> actionAssociated;
	float opacity;
	int type;
	int originalType;
	glTiled(int type);
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
	void showLadder();
protected:
	void executeAction(glAction& action);
};