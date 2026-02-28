#include "Animation.h"

Animation::Animation(std::vector<sf::Texture> frms, int fc, int cf, int spd, std::string n, bool rep) {
	frames = frms;
	frameCount = fc;
	currentFrame = cf;
	speed = spd;
	name = n;
	isRepeat = rep;
}

int& Animation::update(std::string n, int& cf, Entity* ent) {
	currentFrame = cf;
	if (n == name) {
		currentFrame++;
		int frameindex = currentFrame / speed;
		if (isRepeat) {
			frameindex = frameindex % frameCount;
		}
		else {
			frameindex = std::min(frameindex, frameCount - 1);
		}
		ent->getComponent<cSprite>().image.setTexture(frames[frameindex]);
		return currentFrame;
	}
}

std::vector<sf::Texture>& Animation::getFrames() {
	return frames;
}
