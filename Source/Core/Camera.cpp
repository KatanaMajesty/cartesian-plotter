#include <Core/Camera.h>

Camera::Camera(float aspectRatio, float fov)
: fov(fov), position(glm::vec3(0.0f, 0.0f, 3.0f))
, lookPosition(glm::vec3(0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f))
{
	yRenderBorder = position.z * tan(glm::radians(fov / 2.0f));
	xRenderBorder = yRenderBorder * aspectRatio;

	glm::vec2 min = { -xRenderBorder + xOffset, -yRenderBorder + yOffset};
	glm::vec2 max = {  xRenderBorder + xOffset,  yRenderBorder + yOffset };

	aabb = AABB::Create(min, max);
}

void Camera::Update(float aspectRatio)
{
	yRenderBorder = position.z * tan(glm::radians(fov / 2.0f));
	xRenderBorder = yRenderBorder * aspectRatio;

	glm::vec2 min = { -xRenderBorder + xOffset, -yRenderBorder + yOffset};
	glm::vec2 max = {  xRenderBorder + xOffset,  yRenderBorder + yOffset };

	aabb = AABB::Create(min, max);

	position = glm::vec3(xOffset, yOffset, zOffset);
	lookPosition = glm::vec3(xOffset, yOffset, 0.0f);
}
	
bool Camera::IsVisible(Object& object)
{
	return (this->aabb.CollideWith(object.GetAABB()));
}
