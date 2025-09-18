#pragma once

#include <algorithm>



class Rect
{
public:

	Rect() : x(0), y(0), w(0), h(0) {}
	Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

	void absolute();
	void relative();

	bool contains(float px, float py) const;
	bool intersects(const Rect& r) const;

	union {
		float x;	// x of the upper left corner. 
		float x1;	// Alternative name for x.
	};
	union {
		float y;	// y of the upper left corner.
		float y1;	// Alternative name for y.
	};
	union {
		float w;	// width of the rect.
		float x2;	// Alternative name for w.
	};
	union {
		float h;	// height of the rect.
		float y2;	// Alternative name for h.
	};

};
