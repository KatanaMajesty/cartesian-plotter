#include <Core/Camera.h>

Camera::Camera(float aspectRatio, float distance, sol::Vec3f up, float fov)
: fov(fov), position(sol::Vec3f(0.0f, 0.0f, distance))
, lookPosition(sol::Vec3f(0.0f)), up(up), offset(sol::Vec3f(0.0f, 0.0f, 3.0f))
{
	yRenderBorder = position.z * tan(sol::Radians(fov / 2.0f));
	xRenderBorder = yRenderBorder * aspectRatio;

	sol::Vec2f min = { -xRenderBorder + offset.x, -yRenderBorder + offset.y};
	sol::Vec2f max = {  xRenderBorder + offset.x,  yRenderBorder + offset.y};

	aabb = AABB::Create(min, max);
}

void Camera::Update(float aspectRatio)
{
	yRenderBorder = position.z * tan(sol::Radians(fov / 2.0f));
	xRenderBorder = yRenderBorder * aspectRatio;

	sol::Vec2f min = { -xRenderBorder + offset.x, -yRenderBorder + offset.y};
	sol::Vec2f max = {  xRenderBorder + offset.x,  yRenderBorder + offset.y};

	aabb = AABB::Create(min, max);

	position = sol::Vec3f(offset.x, offset.y, offset.z);
	lookPosition = sol::Vec3f(offset.x, offset.y, 0.0f);
}
	
bool Camera::IsVisible(Object& object)
{
	return (this->aabb.CollideWith(object.GetAABB()));
}
