#include <Core/Window.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static void ImGuiInit(GLFWwindow* context)
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

static void ImGuiDestroy()
{
	// Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

Window::Window(int width, int height, const char* title)
: m_Width(width), m_Height(height)
{
	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_Window)
	{
		throw std::runtime_error("window is null");
	}

	glfwMakeContextCurrent(m_Window);
}

Window::~Window()
{
	ImGuiDestroy();
}

void Window::CreateRenderContext()
{
	if (m_Renderer)
	{
		m_Renderer.reset();
	}
	m_Renderer = std::make_unique<Renderer>(this, 2048);
}

void Window::Open()
{
	ImGuiInit(this->Context());
	CreateRenderContext();

	while (!glfwWindowShouldClose(m_Window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.11f, 0.11f, 0.12f, 1.0f);

		m_Renderer->Render();
		m_Renderer->ImGuiRender();

		glViewport(0, 0, m_Width, m_Height);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, true);
}