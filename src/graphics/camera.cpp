#include "camera.h"



/**
 * @brief Construct a Camera.
 * @param width The width of the screen (in pixels).
 * @param height The height of the screen (in pixels).
 */
Camera::Camera(uint32_t width, uint32_t height) :
	m_screen_ratio(width/height),
	m_zoom(1.0f),
	m_zoom_min(0.5f),
	m_zoom_max(2.0f),
	m_viewport(),
	m_raw_viewport()
{

}



/**
 * @brief Set  the camera position.
 * @param x The new value of the x coordinate.
 * @param y The new value of the y coordinate.
 */
void Camera::setPos(float x, float y)
{
	m_raw_viewport.x = x;
	m_raw_viewport.y = y;
	update_viewport();
}

/**
 * @brief Translate the camera.
 * @param dx The translation value on the x axis.
 * @param dy The translation value on the y axis.
 */
void Camera::move(float dx, float dy)
{
	m_raw_viewport.x += dx;
	m_raw_viewport.y += dy;
	update_viewport();
}

/**
 * @brief Translate the camera on the x axis.
 * @param dx The translation value.
 */
void Camera::moveX(float dx)
{
	m_raw_viewport.x += dx;
	update_viewport();
}

/**
 * @brief Translate the camera on the y axis.
 * @param dy The translation value.
 */
void Camera::moveY(float dy)
{
	m_raw_viewport.y += dy;
	update_viewport();
}



/**
 * @brief Set the zoom value.
 * @param dz The new zoom value.
 * @note If the zoom is out of bounds, it will be increased/reduced.
 */
void Camera::setZoom(float z)
{
	m_zoom = z;
	if (m_zoom < m_zoom_min) m_zoom = m_zoom_min;
	if (m_zoom > m_zoom_max) m_zoom = m_zoom_max;
	update_viewport();
}

/**
 * @brief Multiply the zoom value by a factor.
 * @param dz The factor to use.
 * @note If the zoom is out of bounds, it will be increased/reduced.
 */
void Camera::zoom(float dz)
{
	m_zoom *= dz;
	if (m_zoom < m_zoom_min) m_zoom = m_zoom_min;
	if (m_zoom > m_zoom_max) m_zoom = m_zoom_max;
	update_viewport();
}

/**
 * @brief Set the min zoom value.
 * @param z_min The new min.
 * @note If the zoom is out of bounds, it will be increased.
 */
void Camera::setZoomMin(float z_min)
{
	m_zoom_min = z_min;
	if (m_zoom < z_min) {
		m_zoom = z_min;
		update_viewport();
	}
}

/**
 * @brief Set the max zoom value.
 * @param z_max The new max.
 * @note If the zoom is out of bounds, it will be reduced..
 */
void Camera::setZoomMax(float z_max)
{
	m_zoom_max = z_max;
	if (m_zoom > z_max) {
		m_zoom = z_max;
		update_viewport();
	}
}



/**
 * @brief Set the width of the viewport.
 * @param width The new height.
 * @note This is the width when zoom = 1.
 */
void Camera::setWidth(float width)
{
	m_raw_viewport.w = width;
	m_raw_viewport.h = width/m_screen_ratio;
	update_viewport();
}

/**
 * @brief Set the height of the viewport.
 * @param height The new height.
 * @note This is the height when zoom = 1.
 */
void Camera::setHeight(float height)
{
	m_raw_viewport.w = height*m_screen_ratio;
	m_raw_viewport.h = height;
	update_viewport();
}



/**
 * @brief Apply the zoom to the viewport.
 */
void Camera::update_viewport()
{

	const float cx = m_raw_viewport.x + m_raw_viewport.w * 0.5f;
    const float cy = m_raw_viewport.y + m_raw_viewport.h * 0.5f;

    const float half_w = m_raw_viewport.w * m_zoom * 0.5f;
    const float half_h = m_raw_viewport.h * m_zoom * 0.5f;

	m_viewport = glm::ortho(
        cx - half_w, cx + half_w,
        cy - half_h, cy + half_h
    );

}
