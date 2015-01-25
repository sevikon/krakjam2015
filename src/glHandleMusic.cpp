#include "glHandleMusic.h"
#include <iostream>

using namespace std;

void glHandleMusic::HandleMusic()
{	
	Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"press1"));
	if (!Sounds.back().first.loadFromFile("assets/music/press1.ogg")) 
		cout << "Error while loading sounds" << endl;
	Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"press2"));
	if (!Sounds.back().first.loadFromFile("assets/music/press2.ogg")) 
		cout << "Error while loading sounds" << endl;
	Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"press3"));
	if (!Sounds.back().first.loadFromFile("assets/music/press3.ogg")) 
		cout << "Error while loading sounds" << endl;
	Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"press4"));
	if (!Sounds.back().first.loadFromFile("assets/music/press4.ogg")) 
		cout << "Error while loading sounds" << endl;

	/*Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"FallEgg_1"));
	if (!Sounds.back().first.loadFromFile("data/music/FallEgg_1.ogg")) return false;
	Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"CatchEgg_0"));
	if (!Sounds.back().first.loadFromFile("data/music/CatchEgg_0.ogg")) return false;
	Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"CatchEgg_1"));
	if (!Sounds.back().first.loadFromFile("data/music/CatchEgg_1.ogg")) return false;
	Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"Fox"));
	if (!Sounds.back().first.loadFromFile("data/music/fox.ogg")) return false;
	Sounds.push_back(std::pair<sf::SoundBuffer,std::string>(sf::SoundBuffer(),"Door"));
	if (!Sounds.back().first.loadFromFile("data/music/Door.ogg")) return false;*/

	MusicLevel1.openFromFile("assets/music/level1.ogg");
	MusicMenu.openFromFile("assets/music/menu.ogg");
	MusicGameOver.openFromFile("assets/music/gameOver.ogg");

	MusicLevel1.setLoop(true);
	MusicMenu.setLoop(true);

	Players.resize(Sounds.size());
}

void glHandleMusic::PlaySound(std::string name)
{
	int i;

	std::vector<std::pair<sf::SoundBuffer,std::string> >::iterator it;
	for (i = 0; i < Sounds.size(); ++i)
		if (Sounds[i].second == name)
			break;

	Players[i].setBuffer(Sounds[i].first);
	Players[i].play();
}

void glHandleMusic::StopAll()
{
	MusicLevel1.stop();
	MusicMenu.stop();
	MusicGameOver.stop();
}