#include "point.hpp"

point point::operator +(const vec2& other) const
{
	return point {x + other.x, y + other.y};
}
bool point::operator ==(const point& other) const
{
	return x == other.x && y == other.y;
}
