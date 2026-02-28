#pragma once
#include "Animation.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include <map>

class Assets
{
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, Animation> animations;
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, sf::Font> fonts;

public:
	Assets();
	Assets(std::string path);
	void addTexture(std::string name, std::string path);
	void addAnimation(std::string name, Animation animation);
	void addSound(std::string, std::string path);
	void addFont(std::string name, std::string path);

	sf::Texture& getTexture(std::string name);
	Animation& getAnimation(std::string name);
	sf::SoundBuffer& getSound(std::string);
	sf::Font& getFont(std::string name);
};

