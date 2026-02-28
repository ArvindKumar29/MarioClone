#pragma once
#include "Entity.h"
#include "Line.h"
#include "Vec2.h"

class Physics
{
public:
	static Vec2 getOverlap(Entity* a, Entity* b);
	static Vec2 getPrevOverlap(Entity* a, Entity* b);

};

