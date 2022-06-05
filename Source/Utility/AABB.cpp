#include <Utility/AABB.h>

bool AABB::CollideWith(const Vertex& vertex) const
{
	const glm::vec2& pos = vertex.position;
	return (pos.x >= this->min.position.x && pos.x <= this->max.position.x) 
		&& (pos.y >= this->min.position.y && pos.y <= this->max.position.y); 
}

bool AABB::CollideWith(const glm::vec2 pos) const
{
	return (pos.x >= this->min.position.x && pos.x <= this->max.position.x) 
		&& (pos.y >= this->min.position.y && pos.y <= this->max.position.y); 
}

bool AABB::CollideWith(const AABB& box) const
{
	return (box.min.position.x <= this->max.position.x && box.max.position.x >= this->min.position.x)
		&& (box.min.position.y <= this->max.position.y && box.max.position.y >= this->min.position.y);
}

AABB AABB::Transform(const glm::mat4& model)
{

	AABB aabb = operator*(model, *this);
	glm::vec4 color = aabb.max.color;	// odd

	float xMin = aabb.min.position.x, yMin = aabb.min.position.y;
	float xMax = aabb.max.position.x, yMax = aabb.max.position.y;

	xMin = std::min<float>(xMin, aabb.p1.position.x);
	xMin = std::min<float>(xMin, aabb.p3.position.x);
	xMin = std::min<float>(xMin, aabb.max.position.x);

	xMax = std::max<float>(xMax, aabb.p1.position.x);
	xMax = std::max<float>(xMax, aabb.p3.position.x);
	xMax = std::max<float>(xMax, aabb.min.position.x);

	yMin = std::min<float>(yMin, aabb.p1.position.y);
	yMin = std::min<float>(yMin, aabb.p3.position.y);
	yMin = std::min<float>(yMin, aabb.max.position.y);

	yMax = std::max<float>(yMax, aabb.p1.position.y);
	yMax = std::max<float>(yMax, aabb.p3.position.y);
	yMax = std::max<float>(yMax, aabb.min.position.y);

	aabb.p1 = Vertex(xMin, yMax, color);
	aabb.max = Vertex(xMax, yMax, color);
	aabb.p3 = Vertex(xMax, yMin, color);
	aabb.min = Vertex(xMin, yMin, color);

	return aabb;
}

std::ostream& operator<<(std::ostream& stream, const AABB& aabb)
{
	stream << aabb.p1 << std::endl 
		<< aabb.max << std::endl
		<< aabb.p3 << std::endl
		<< aabb.min << std::endl;
	return stream;
}

AABB operator*(const glm::mat4& mat, AABB& aabb)
{
	aabb.p1 = mat * aabb.p1;
	aabb.max = mat * aabb.max;
	aabb.p3 = mat * aabb.p3;
	aabb.min = mat * aabb.min;
	return aabb;
}

AABB AABB::Create(const std::vector<Vertex>& vec)
{
	if (vec.empty())
	{
		return {};
	}

	Vertex min = vec.front();
	Vertex max = min;

	for (const Vertex& vert : vec)
	{
		if (vert.position.x < min.position.x)
		{
			min.position.x = vert.position.x;
		}
		else if (vert.position.x > max.position.x)
		{
			max.position.x = vert.position.x;
		}
		if (vert.position.y < min.position.y)
		{
			min.position.y = vert.position.y;
		}
		else if (vert.position.y > max.position.y)
		{
			max.position.y = vert.position.y;
		}
	}

	return { Vertex(min.position.x, max.position.y, min.color)
		, max
		, Vertex(max.position.x, min.position.y, max.color)
		, min };
}

AABB AABB::Create(glm::vec2 min, glm::vec2 max, glm::vec4 color)
{
	return { Vertex(min.x, max.y, color), Vertex(max, color), Vertex(max.x, min.y, color), Vertex(min, color) };
}
