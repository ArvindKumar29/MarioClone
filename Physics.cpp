#include "Physics.h"
#include <iostream>

Vec2 Physics::getOverlap(Entity* a, Entity* b) {
	auto x1 = a->getComponent<cTransform>().pos.x;
	auto y1 = a->getComponent<cTransform>().pos.y;
	auto x2 = b->getComponent<cTransform>().pos.x;
	auto y2 = b->getComponent<cTransform>().pos.y;
	auto w1 = a->getComponent<cBoundingBox>().w;
	auto h1 = a->getComponent<cBoundingBox>().h;
	auto w2 = b->getComponent<cBoundingBox>().w;
	auto h2 = b->getComponent<cBoundingBox>().h;

	

	float dx = std::abs(x1 - x2);
	float dy = std::abs(y1 - y2);
	auto overlapx = (w1 / 2) + (w2 / 2) - dx;
	auto overlapy = (h1 / 2) + (h2 / 2) - dy;

	//std::cout << "Player W: " << w1 << " | Tile W: " << w2 << " | Overlap Y: " << overlapy << "\n";

	auto overlap = Vec2(overlapx, overlapy);
	return overlap;
}

Vec2 Physics::getPrevOverlap(Entity* a, Entity* b) {
	auto x1 = a->getComponent<cTransform>().prevPos.x;
	auto y1 = a->getComponent<cTransform>().prevPos.y;
	auto x2 = b->getComponent<cTransform>().prevPos.x;
	auto y2 = b->getComponent<cTransform>().prevPos.y;
	auto w1 = a->getComponent<cBoundingBox>().w;
	auto h1 = a->getComponent<cBoundingBox>().h;
	auto w2 = b->getComponent<cBoundingBox>().w;
	auto h2 = b->getComponent<cBoundingBox>().h;

	float dx = std::abs(x1 - x2);
	float dy = std::abs(y1 - y2);
	auto overlapx = (w1 / 2) + (w2 / 2) - dx;
	auto overlapy = (h1 / 2) + (h2 / 2) - dy;

	auto overlap = Vec2(overlapx, overlapy);
	return overlap;
}