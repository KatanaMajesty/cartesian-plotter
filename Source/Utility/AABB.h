#pragma once

#include <vector>
#include <Utility/Vertex.h>

/*
	Axis-aligned Bounding Box with the next structure:
	p1 ------- max	 
 	!			!
 	!			!
 	!			!
 	!			!
 	min ------ p3
*/
struct AABB
{
	Vertex p1;
	Vertex max;
	Vertex p3;
	Vertex min;

	// Check for collision
	bool CollideWith(const Vertex&) const;
	bool CollideWith(const sol::Vec2f) const;
	bool CollideWith(const AABB&) const;
	// This method allows to transform AABB with model matrix
	// This is very important so that we avoid multiplying every object 
	// vertex on CPU and only manipulate AABB
	AABB Transform(const sol::Mat4f& model);

	// overloaded operators for ostream& and matrix multiplication
	friend std::ostream& operator<<(std::ostream& stream, const AABB& aabb);
	friend AABB operator*(const sol::Mat4f& mat, AABB& aabb);

	// Creates AABB from the given parameter
	// Note that creating AABB from vector is O(n), although creating AABB with (min, max) is O(1)
	static AABB Create(const std::vector<Vertex>& vec);
	static AABB Create(sol::Vec2f min, sol::Vec2f max, sol::Vec4f color = sol::Vec4f(0.9f, 0.6f, 0.3f, 1.0f));
};