#pragma once

// Thirdparty & STD includes
#include <glm/glm.hpp>

// Project Includes
#include <Utility/AABB.h>
#include <Core/Object.h>

/**
 * 	@brief Camera represents a simple camera with it's vectors, fov and offsets.
 */
class Camera
{
public:
	Camera(float aspectRatio, float fov = 45.0f);

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

	float xOffset = 0.0f;
	float yOffset = 0.0f;
	float zOffset = 3.0f;

	AABB aabb;
};