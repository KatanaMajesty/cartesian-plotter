#include <Utility/Vertex.h>

Vertex::Vertex(float x, float y, glm::vec4 color)
: position(glm::vec2(x, y)), color(color) {}

Vertex::Vertex(float x, float y, float r, float g, float b, float a)
: position(glm::vec2(x, y)), color(glm::vec4(r, g, b, a)) {}

Vertex::Vertex(glm::vec2 pos, glm::vec4 color)
: position(pos), color(color) {}

std::ostream& operator<<(std::ostream& stream, const Vertex& v)
{
	stream << v.position.x << ", " << v.position.y;
	return stream;
}

Vertex& operator*(const glm::mat4& mat, Vertex& vertex)
{
	vertex.position = glm::vec2(mat * glm::vec4(vertex.position, 0.0f, 1.0f));
	return vertex;
}

Vertex operator*(const glm::mat4& mat, const Vertex& vertex)
{
	return Vertex(glm::vec2(mat * glm::vec4(vertex.position, 0.0f, 1.0f)), vertex.color);
}

bool Vertex::operator==(const Vertex& other)
{
	return this->position == other.position;
}

bool Vertex::operator!=(const Vertex& other)
{
	return !(*this == other);
}
