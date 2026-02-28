#pragma once
#include "Vec2.h"

class Line {
public:
	Vec2 a;
	Vec2 b;

	Line(Vec2 a, Vec2 b) {
		a = a;
		b = b;
	}

	Line operator - (const Line& other) const;
};

