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

	sf::View playerView;

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
		CLIMBUP = 1,
		CLIMBDOWN = 2,
		RIGHT = 4,
		LEFT = 8,
		FALL = 16,
		NONE = 32,
		RIGHTBORDER = 64,
		LEFTBORDER = 128
	};

	enum PLAYER {
		FST,
		SND
	};

	bool death;

	event lastEvent;
	PLAYER playerId;
	int side;
	sf::Vector2f position;

	int getWidth();
	int getHeight();
	sf::Sprite& getSpirte() {return sprite;}

	void Load(int _side);
	void Init(float x, float y, sf::View View, glHero::PLAYER _playerId);
	void Update(event _event);
	void UpdateReverse(event _event);
	void Draw(sf::RenderWindow& graphics);

};
