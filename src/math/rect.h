#pragma once

#include <algorithm>



class Rect
{
public:

	Rect() : x(0), y(0), w(0), h(0) {}
	Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

	bool contains(float px, float py) const;
	bool intersects(const Rect& r) const;

	float x;	// x of the upper left corner. 
	float y;	// y of the upper left corner.
	float w;	// width of the rect.
	float h;	// height of the rect.

};
