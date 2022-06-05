#pragma once

// Thirdparty & STD includes
#include <glm/glm.hpp>

/**
 * 	Vertex structure is a wrapper for OpenGL vertex
 * 	In this project it consists of vec2 (xy) position and vec4 color (rgba)
 */
struct Vertex
{
	Vertex() = default;
	Vertex(float x, float y, glm::vec4 color);
	Vertex(float x, float y, float r, float g, float b, float a);
	Vertex(glm::vec2 pos, glm::vec4 color);
	~Vertex() = default;

	// overloaded operators for ostream& and matrix multiplication
	friend std::ostream& operator<<(std::ostream& stream, const Vertex& v);
	friend Vertex& operator*(const glm::mat4& mat, Vertex& vertex);
	friend Vertex operator*(const glm::mat4& mat, const Vertex& vertex);
	
	// boolean comparison operators
	bool operator==(const Vertex&);
	bool operator!=(const Vertex&);

	glm::vec2 position;
	glm::vec4 color;
};