#pragma once

#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../math/rect.h"



class Camera
{
public:

	Camera(uint32_t width, uint32_t height);
	~Camera() = default;

	void setPos(float x, float y);
	void move(float dx, float dy);
	void moveX(float dx);
	void moveY(float dy);

	void setZoom(float z);
	void zoom(float dz);
	void setZoomMin(float z_min);
	void setZoomMax(float z_max);

	void setWidth(float width);
	void setHeight(float height);

	float getZoom() const { return m_zoom; }
	float getZoomMin() const { return m_zoom_min; }
	float getZoomMax() const { return m_zoom_max; }
	float getScreenRatio() const { return m_screen_ratio; }
	const glm::mat4 &getViewport() const { return m_viewport; }

private:

	void update_viewport();

	const float m_screen_ratio;	// Screen ratio.

	float m_zoom;		// Zoom value.
	float m_zoom_min;	// Min zoom value.
	float m_zoom_max;	// Max zoom value.

	glm::mat4 m_viewport;	// Viewport of the camera after applying the zoom.
	Rect m_raw_viewport;	// Viewport of the camera without the zoom.

};
