#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class glTiled;

class glAction
{
protected:
	virtual void execute(sf::Sprite& sprite) = 0;
};

namespace actions {
	class fadeOut : public glAction
	{
		void execute(glTiled& tile);
	};

	class fadeIn : public glAction
	{
		void execute(glTiled& tile);
	};
}