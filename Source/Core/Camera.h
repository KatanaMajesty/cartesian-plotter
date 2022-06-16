#pragma once

#include <Utility/AABB.h>
#include <Core/Object.h>

/**
 * 	@brief Camera represents a simple camera with it's vectors, fov and offsets.
 */
class Camera
{
public:
	Camera(float aspectRatio, float distance = 5.0f, sol::Vec3f up = sol::Vec3f(0.0f, 1.0f, 0.0f), float fov = 45.0f);

	// Updates camera's render borders, AABB, position and look position
	void Update(float aspectRatio);
	// Checks whether an object is visible in camera. Should be used for object culling
	// to avoid redundant renderer drawcalls
	bool IsVisible(Object& object);

	// Camera's data
	float fov;
	// Components for lookAt matrix
	sol::Vec3f position;
	sol::Vec3f lookPosition;
	sol::Vec3f up;

	float xRenderBorder;
	float yRenderBorder;

	sol::Vec3f offset;

	AABB aabb;
};