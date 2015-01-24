#pragma once
#include "SFML\Audio.hpp"

class glHandleMusic
{
public: 
	sf::Music MusicLevel1, MusicMenu;
	std::vector<std::pair<sf::SoundBuffer,std::string> > Sounds;
	std::vector<sf::Sound> Players;

	void HandleMusic();
	void PlaySound(std::string name);
};