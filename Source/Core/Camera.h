#pragma once

#include <glm/glm.hpp>

struct Camera
{
	float fov;
	glm::vec3 position;
	glm::vec3 lookPosition;
	glm::vec3 up;
};