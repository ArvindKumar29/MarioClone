#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Animation
{
	std::string name;
	int frameCount, currentFrame, speed;
	std::vector<sf::Texture> frames;
	bool isRepeat;

public:
	Animation() {}
	Animation(std::vector<sf::Texture> frames,  int frameCount, int currentFrame, int speed, std::string name, bool isRepeat);
	int& update(std::string name , int& currentFrame, Entity* entity);
	std::vector<sf::Texture>& getFrames();
};

