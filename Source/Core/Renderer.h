#pragma once

#include <Core/Shader.h>
#include <Core/Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>
#include <vector>

struct Vertex
{
	glm::vec2 position;
};

struct Line
{
	Vertex a, b;
	inline constexpr size_t Vertices() const { return 2; }
};

struct Triangle
{
	Vertex a, b, c;
	inline constexpr size_t Vertices() const { return 3; }
};

struct Quad
{
	Vertex a, b, c, d;
	inline constexpr size_t Vertices() const { return 4; }
};

// forward declaration
class Window;

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