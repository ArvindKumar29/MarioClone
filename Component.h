#pragma once
#include "Vec2.h"
#include<SFML/Graphics.hpp>

struct cTransform {
	Vec2 pos;
	Vec2 prevPos;
	Vec2 vel;
	Vec2 scale;
	float angle;
	bool has = false;

	cTransform() {};
	cTransform(const Vec2& p, const Vec2& v, const Vec2& s, float a) : pos(p), vel(v), scale(s), angle(a) {};
};

struct cBoundingBox {
	sf::RectangleShape BBox;
	float w, h;
	bool has = false;

	cBoundingBox() {};
	cBoundingBox(float w, float h) {
		this->w = w;
		this->h = h;
		BBox.setSize({w, h});
		BBox.setOrigin(w / 2, h / 2);
	}
};

struct cSprite {
	sf::Sprite image;
	bool has = false;

	cSprite() {};
	cSprite(sf::Sprite image) {
		image = image;
	}
};

struct cAnimation {
	//std::vector<sf::Texture> anim;
	int currentFrame = 0;
	std::string name;
	bool has = false;

	cAnimation() {};
	cAnimation(std::string n) {
		this->name = n;
		this->has = true;
	}
};

struct cInput {
	bool jump;
	bool left;
	bool right;
	bool has = false;

	cInput() {
		jump = false;
		left = false;
		right = false;
	}
};

struct cGravity {
	float gravity;
	bool has = false;

	cGravity() {
		gravity = 0.5f;
	}
	cGravity(float grav) {
		gravity = grav;
	}
};