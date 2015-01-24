#pragma once
#include "SFML\Audio.hpp"

class glHandleMusic
{
public: 
	sf::Music MusicLevel1, MusicMenu, MusicGameOver;
	std::vector<std::pair<sf::SoundBuffer,std::string> > Sounds;
	std::vector<sf::Sound> Players;

	void StopAll();
	void HandleMusic();
	void PlaySound(std::string name);
};