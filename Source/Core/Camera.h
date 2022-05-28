#pragma once

// Thirdparty & STD includes
#include <glm/glm.hpp>

/**
 * 	@brief Camera represents a simple camera structure with it's vectors and fov.
 */
struct Camera
{
	float fov;
	glm::vec3 position;
	glm::vec3 lookPosition;
	glm::vec3 up;
};