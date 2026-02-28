#include "Line.h"

Line Line::operator-(const Line& other) const {
	return Line(this->a - other.a, this->b - other.b);
}