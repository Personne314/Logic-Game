#include "rect.h"



/**
 * @brief Convert the coordinates from relative system (x,y,w,h) to absolute system (x1,y1,x2,y2).
 */
void Rect::absolute()
{
	x2 += x;
	y2 += y;
}

/**
 * @brief Convert the coordinates from absolute system (x1,y1,x2,y2) to relative system (x,y,w,h).
 */
void Rect::relative()
{
	w -= x;
	y -= y;
}



/**
 * @brief Check if a point is in the rect.
 * @param px the x coordinate of the point.
 * @param py the y coordinate of the point.
 * @return true if the point is in the rect.
 */
bool Rect::contains(float px, float py) const
{
	return px >= x && px <= x+w && py >= y && py <= y+h;
}

/**
 * @brief Check if two rects intersects.
 * @param r The second rect.
 * @return true if the rects intersects.
 */
bool Rect::intersects(const Rect& r) const
{
	return x+w >= r.x && x <= r.x+r.w && y+h >= r.y && y <= r.y+r.h;
}
