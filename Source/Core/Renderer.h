#pragma once

#include <Core/Shader.h>

#include <glm/glm.hpp>

#include <unordered_map>

struct Vertex
{
	glm::vec2 position;
};

class Renderer
{
public:
	using ShaderMap = std::unordered_map<const char*, std::shared_ptr<Shader>>;
public:
	Renderer(GLFWwindow* context, size_t vertices);
	~Renderer() = default;

	void Render();
	void ImGuiRender();

	void MapShader(const char* name);
	Shader& FindShader(const char* name);
private:
	GLFWwindow* m_Context;
	
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_Program;
	size_t m_Vertices;

	ShaderMap m_ShaderMap;
};