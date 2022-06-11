#pragma once

// Thirdparty & STD includes
#include <glm/glm.hpp>
#include <Utility/Matrix.h>

/**
 * 	Vertex structure is a wrapper for OpenGL vertex
 * 	In this project it consists of vec2 (xy) position and vec4 color (rgba)
 */
struct Vertex
{
	Vertex() = default;
	Vertex(float x, float y, sol::Vec4f color);
	Vertex(float x, float y, float r, float g, float b, float a);
	Vertex(sol::Vec2f pos, sol::Vec4f color);
	~Vertex() = default;

	// overloaded operators for ostream& and matrix multiplication
	friend std::ostream& operator<<(std::ostream& stream, const Vertex& v);
	friend Vertex& operator*(const sol::Mat4f& mat, Vertex& vertex);
	friend Vertex& operator*(const glm::mat4& mat, Vertex& vertex);
	// friend Vertex operator*(const sol::Mat4f& mat, const Vertex& vertex);
	
	// boolean comparison operators
	bool operator==(const Vertex&);
	bool operator!=(const Vertex&);

	sol::Vec2f position;
	sol::Vec4f color;
};