#include <Core/Renderer.h>
#include <Core/Window.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

std::shared_ptr<Shader> basicShader;
glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;

// Overall data
Renderer::Renderer(Window* const window, size_t vertices)
: m_Window(window), m_Vertices(vertices)
{
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("glew init");
	}

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

	basicShader = MapShader("Basic");

	// Setup axes
	Line xAxis;
	xAxis.a = { glm::vec2(-1.0f, 0.0f) };
	xAxis.b = { glm::vec2(1.0f, 0.0f) };

	Line yAxis;
	yAxis.a = { glm::vec2(0.0f, -1.0f) };
	yAxis.b = { glm::vec2(0.0f, 1.0f) };

	Quad quad;
	quad.a = { glm::vec2(-0.5f, 0.5f) };
	quad.b = { glm::vec2(0.5f, 0.5f) };
	quad.c = { glm::vec2(0.5f, -0.5f) };
	quad.d = { glm::vec2(-0.5f, -0.5f) };

	PushDrawData(GL_LINES, reinterpret_cast<Vertex*>(&yAxis), xAxis.Vertices());
	PushDrawData(GL_LINE_LOOP, reinterpret_cast<Vertex*>(&quad), quad.Vertices());
	PushDrawData(GL_LINES, reinterpret_cast<Vertex*>(&xAxis), xAxis.Vertices());

 	m_Camera.fov = 45.0f;
 	m_Camera.position = glm::vec3(0.f, 0.f, 3.f);
 	m_Camera.lookPosition = glm::vec3(0.f);
 	m_Camera.up = glm::vec3(0.f, 1.f, 0.f);

	::projection = glm::perspective(m_Camera.fov, m_Window->AspectRatio(), 0.1f, 1000.0f);
	::view = glm::lookAt(m_Camera.position, m_Camera.lookPosition, m_Camera.up);
	::model = glm::mat4(1.f);
}

// This method will be called each frame in main loop
void Renderer::Render() 
{
	Shader::Bind(*basicShader);
	
	// glm::mat4
	basicShader->SetUniformMat4("u_Projection", ::projection);
	basicShader->SetUniformMat4("u_View", ::view);
	basicShader->SetUniformMat4("u_Model", ::model);

	FlushDrawData();

	::projection = glm::perspective(m_Camera.fov, m_Window->AspectRatio(), 0.1f, 1000.0f);
	::view = glm::lookAt(m_Camera.position, m_Camera.lookPosition, m_Camera.up);
}

// This ImGui context method will be called each frame in main loop
void Renderer::ImGuiRender() 
{
	ImGui::Begin("Hello, ImGui!");

	ImGui::End();
}

std::shared_ptr<Shader> Renderer::MapShader(const char* name)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(name);
	m_ShaderMap.insert(std::make_pair( name, shader ));
	return shader;
}

Shader& Renderer::FindShader(const char* name)
{
	ShaderMap::iterator iter = m_ShaderMap.find(name);
	if (iter == m_ShaderMap.end())
	{
		throw std::runtime_error("Failed to find shader");
	}

	return *iter->second;
}

void Renderer::PushDrawData(unsigned int drawMode, Vertex* data, size_t count)
{
	std::vector<Vertex>& vec = m_DynamicBatching[drawMode];
	for (size_t i = 0; i < count; i++)
	{
		vec.push_back(*(data + i));
	}
}

void Renderer::FlushDrawData()
{
	size_t offset = 0;
	for (auto& pair : m_DynamicBatching)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), pair.second.size() * sizeof(Vertex), pair.second.data());
		glDrawArrays(pair.first, offset, pair.second.size());
		offset += pair.second.size();
	}
}
