#include "vec2.hpp"

bool vec2::operator ==(const vec2& other) const
{
	return x == other.x && y == other.y;
}
bool vec2::operator !=(const vec2& other) const
{
	return !(*this == other);
}
