#pragma once

// Thirdparty & STD includes
#include <vector>
#include <glm/glm.hpp>

// Project Includes
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
	bool CollideWith(const glm::vec2) const;
	bool CollideWith(const AABB&) const;
	// This method allows to transform AABB with model matrix
	// This is very important so that we avoid multiplying every object 
	// vertex on CPU and only manipulate AABB
	AABB Transform(const glm::mat4& model);

	// overloaded operators for ostream& and matrix multiplication
	friend std::ostream& operator<<(std::ostream& stream, const AABB& aabb);
	friend AABB operator*(const glm::mat4& mat, AABB& aabb);

	// Creates AABB from the given parameter
	// Note that creating AABB from vector is O(n), although creating AABB with (min, max) is O(1)
	static AABB Create(const std::vector<Vertex>& vec);
	static AABB Create(glm::vec2 min, glm::vec2 max, glm::vec4 color = glm::vec4(0.9f, 0.6f, 0.3f, 1.0f));
};