#include "rect.h"



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
