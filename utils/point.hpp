#pragma once
#include "vec2.hpp"

struct point
{
	int x, y;
	point operator+(const vec2& direction) const;
	bool operator ==(const point& other) const;
};




