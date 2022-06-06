#include <Core/Camera.h>

Camera::Camera(float aspectRatio, float fov)
: fov(fov), position(sol::Vec3f(0.0f, 0.0f, 3.0f))
, lookPosition(sol::Vec3f(0.0f)), up(sol::Vec3f(0.0f, 1.0f, 0.0f))
{
	yRenderBorder = position.z * tan(sol::Radians(fov / 2.0f));
	xRenderBorder = yRenderBorder * aspectRatio;

	sol::Vec2f min = { -xRenderBorder + xOffset, -yRenderBorder + yOffset};
	sol::Vec2f max = {  xRenderBorder + xOffset,  yRenderBorder + yOffset };

	aabb = AABB::Create(min, max);
}

void Camera::Update(float aspectRatio)
{
	yRenderBorder = position.z * tan(glm::radians(fov / 2.0f));
	xRenderBorder = yRenderBorder * aspectRatio;

	sol::Vec2f min = { -xRenderBorder + xOffset, -yRenderBorder + yOffset};
	sol::Vec2f max = {  xRenderBorder + xOffset,  yRenderBorder + yOffset };

	aabb = AABB::Create(min, max);

	position = sol::Vec3f(xOffset, yOffset, zOffset);
	lookPosition = sol::Vec3f(xOffset, yOffset, 0.0f);
}
	
bool Camera::IsVisible(Object& object)
{
	return (this->aabb.CollideWith(object.GetAABB()));
}
