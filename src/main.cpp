#include <SFML/Graphics.hpp>
#include <iostream>
#include "glSettings.h"
#include "glUtils.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	sf::Texture texture;
	sf::Sprite sprite;

	std::cout << "The Game has started! :)";

	if(!texture.loadFromFile(concat(glSettings::ASSETS_PATH, "bg.png")));

	sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}