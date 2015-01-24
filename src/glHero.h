#pragma once

#include <SFML/Graphics.hpp>

class glHero
{	
private:

	// animations

	sf::Texture imageWalkingLeft[7];
	sf::Texture imageWalkingRight[7];
	sf::Texture imageClimbingDown[7];
	sf::Texture imageClimbingUp[7];
	sf::Texture imageIdle;

	sf::Sprite sprite;

	int currentFrame;

	float animationTimer;

	// properties

	static const int walkingFrames;
	static const int climbingFrames;
	static const float frameDuration;
	static const float climbingSpeed;
	static const float walkingSpeed;
	static const float fallingSpeed;

public:
	
	enum event {
		CLIMBUP = 0,
		CLIMBDOWN = 1,
		RIGHT = 2,
		LEFT = 4,
		FALL = 8,
		NONE = 16
	};

	event lastEvent;
	int side;
	sf::Vector2f position;

	void Load(int _side);
	void Init();
	void Update(event _event);
	void Draw(sf::RenderWindow& graphics);
};
