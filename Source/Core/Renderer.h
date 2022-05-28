#pragma once

// Thirdparty & STD includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_map>
#include <vector>

// Project Includes
#include <Core/Shader.h>
#include <Core/Camera.h>

// Simple primitives and Vertex information
struct Vertex
{
	glm::vec2 position;
};

struct Line
{
	Vertex a, b;
	inline constexpr size_t Vertices() const noexcept { return 2; }
};

struct Triangle
{
	Vertex a, b, c;
	inline constexpr size_t Vertices() const noexcept { return 3; }
};

struct Quad
{
	Vertex a, b, c, d;
	inline constexpr size_t Vertices() const noexcept { return 4; }
};

// forward declaration
class Window;	// TODO: Remove forward declaration

/**
 * 	Renderer class represents an object, that allows to render primitives, 
 * 	attach shaders and manipulate with Window object it's context is stored in.
 * 
 * 	Since 27.05 Renderer uses dynamic batching map, which most likely will be rewritten soon.
 * 	Now it takes in draw mode, e.g. GL_LINES or GL_TRIANGLE and adds vertices to respective bucket in map
 *  Number of drawcalls will be equal to the number of map's buckets
 * 	
 * 	Renderer constructor takes in a Window object pointer and a number of maximum vertices
 * 	in dynamic batching map. It's used in order to setup OpenGL state machine, e.g. VAO, VBO, shaders, etc.
 * 	GLEW and GL functions are also initialized in Renderer's constructor
 * 
 * 	Render() & ImGuiRender methods called each frame in @see @ref Window main-loop.
 * 
 * 	In order to draw primitives, that were pushed into dynamic batching map using PushDrawData() method,
 * 	FlushDrawData() method should be used
 * 
 * 	Shaders are stored in map, that represents <const char*, @see @ref Shader> pair.
 * 	They may be accessed anywhere in object's scope with method FindShader() once MapShader() method is used.
 */	
class Renderer
{
public:
	using ShaderMap = std::unordered_map<const char*, std::shared_ptr<Shader>>;
	using DynamicBatchMap = std::unordered_map<unsigned int, std::vector<Vertex>>;
public:
	Renderer(Window* const window, size_t vertices);
	~Renderer() = default;

	void Render();
	void ImGuiRender();

	// TODO: Should be rewritten to something more efficient
	std::shared_ptr<Shader> MapShader(const char* name);
	Shader& FindShader(const char* name);

	void PushDrawData(unsigned int drawMode, Vertex* data, size_t count);
	void FlushDrawData();
private:	
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_Program;
	size_t m_Vertices;
	Window* const m_Window;

	Camera m_Camera;

	ShaderMap m_ShaderMap;
	/*
	Dynamic Batching map adds primitives into unordered map by a key - Draw Mode
	As a reference I used Unity documentation on Dynamic Batching
	https://docs.unity3d.com/Manual/dynamic-batching.html

	It's good for low-poly or for low-line objects. 
	Drawcall count will be equal to amount of buckets in unordered map, thus equal to Draw Mode amount
	*/
	DynamicBatchMap m_DynamicBatching;
};