#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "glSettings.h"
#include "glUtils.h"

float viewWidth;
float viewHeight;

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "KrakJam 2015"/*, sf::Style::Fullscreen*/);

	// inicjalizacja naszzego widoku (view) i jego rozmiarów
	float windowHeight = (float)window.getSize().y;
	float viewScale = 768.0f/windowHeight;
	viewWidth = window.getSize().x*viewScale;
	viewHeight = 768;
	sf::View view(sf::FloatRect(0, 0, viewWidth, viewHeight));
	window.setView(view);
    
	// uruchom generator liczb losowych
	srand((unsigned)time(NULL));

	sf::Clock frame_timer;
	const float DELTA = 1.0f/60.0f;

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
			if (event.type == sf::Event::Resized)
			{
				float width = window.getSize().x;
				float height = window.getSize().y;

				// Minimum size

				if(width < 800)
					width = 800;
				if(height < 600)
					height = 600;
				if (width<(5.0f/4.0f)*height) 
					width=(5.0f/4.0f)*height;
				if (width>2*height) 
					height=1.0f/2.0f*width;
				window.setSize(sf::Vector2u(width, height));
			}
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}