#include <Core/Renderer.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void ImGuiInit(GLFWwindow* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// Enable Docking
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
    	ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(context, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

// Overall data
Renderer::Renderer(GLFWwindow* context, size_t vertices)
: m_Context(context), m_Vertices(vertices)
{
	ImGuiInit(m_Context);

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

	MapShader("Basic");
}

// This method will be called each frame in main loop
void Renderer::Render() 
{
	Shader::Bind(FindShader("Basic"));
	Vertex pos[5] {
		{glm::vec2(-0.5f, 0.5f)},
		{glm::vec2(0.5f, 0.5f)},
		{glm::vec2(0.5f, -0.5f)},
		{glm::vec2(-0.5f, -0.5f)},
		{glm::vec2(-0.5f, 0.5f)},
	};
	// std::cout << sizeof(pos) << std::endl;
	glBufferSubData(GL_ARRAY_BUFFER, 0, 5 * sizeof(Vertex), &pos[0]);
	glDrawArrays(GL_LINE_STRIP, 0, 5);
}

// This ImGui context method will be called each frame in main loop
void Renderer::ImGuiRender() 
{

}

void Renderer::MapShader(const char* name)
{
	m_ShaderMap.insert(std::make_pair( name, std::make_shared<Shader>(name) ));
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