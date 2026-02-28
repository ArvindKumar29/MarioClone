#include "Assets.h"
#include <fstream>
#include <iostream>

// CONSTRUCTOR
Assets::Assets() {}

Assets::Assets(std::string path) {
	std::fstream fin(path);
	if (!fin.is_open()) {
		std::cout << "Could not load assets source file...";
	}
	std::string type, data, name;
	while (fin >> type) {
		if (type == "Texture") {
			// Texture Name Path
			fin >> name >> data;
			addTexture(name, data);
		}
		else if (type == "Animation") {
			// Animation AnimName FrameCount <All frames one by one> Speed isRepeat
			int fc, speed, startx, starty;
			bool rep;
			fin >> name >> fc;
			int i = 0; auto frames = std::vector<sf::Texture>();
			std::string frameName;
			while (i < fc) {
				fin >> frameName;
				frames.push_back(getTexture(frameName));
				i++;
			}
			fin >> speed >> rep;
			addAnimation(name, Animation(frames, fc, 0, speed, name, rep));
		}
		else if (type == "Font") {
			// Font Name Path
			fin >> name >> data;
			addFont(name, data);
		}
		else if (type == "Sound") {
			// Sound Name path
			fin >> name >> data;
			addSound(name, path);
		}
		//std::cout << "Asset Loaded: " << name << "\n";

	}
}


// SETTERS/ADDING ASSETS
void Assets::addTexture(std::string name, std::string path) {
	textures[name].loadFromFile(path);
}

void Assets::addFont(std::string name, std::string path) {
	fonts[name].loadFromFile(path);
}

void Assets::addSound(std::string name, std::string path) {
	soundBuffers[name].loadFromFile(path);
}

void Assets::addAnimation(std::string name, Animation animation) {
	animations[name] = animation;
}

// GETTERS
sf::Texture& Assets::getTexture(std::string name) {
	return textures[name];
}

sf::SoundBuffer& Assets::getSound(std::string name) {
	return soundBuffers[name];
}

sf::Font& Assets::getFont(std::string name) {
	return fonts[name];
}

Animation& Assets::getAnimation(std::string name) {
	return animations[name];
}