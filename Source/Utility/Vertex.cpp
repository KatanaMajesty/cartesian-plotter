#include <Utility/Vertex.h>
#include <Utility/Matrix.h>

Vertex::Vertex(float x, float y, sol::Vec4f color)
: position(sol::Vec2f(x, y)), color(color) {}

Vertex::Vertex(float x, float y, float r, float g, float b, float a)
: position(sol::Vec2f(x, y)), color(sol::Vec4f(r, g, b, a)) {}

Vertex::Vertex(sol::Vec2f pos, sol::Vec4f color)
: position(pos), color(color) {}

std::ostream& operator<<(std::ostream& stream, const Vertex& v)
{
	stream << v.position.x << ", " << v.position.y;
	return stream;
}

Vertex& operator*(const sol::Mat4f& mat, Vertex& vertex)
{
	vertex.position = sol::Vec2f(mat * sol::Vec4f(vertex.position, 0.0f, 1.0f));
	return vertex;
}

Vertex operator*(const sol::Mat4f& mat, const Vertex& vertex)
{
	return Vertex(sol::Vec2f(mat * sol::Vec4f(vertex.position, 0.0f, 1.0f)), vertex.color);
}

bool Vertex::operator==(const Vertex& other)
{
	return this->position == other.position;
}

bool Vertex::operator!=(const Vertex& other)
{
	return !(*this == other);
}
