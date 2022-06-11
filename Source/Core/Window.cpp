#include <Core/Window.h>
#include <Renderer.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static ImGuiIO& ImGuiInit(GLFWwindow* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// Enable Multi-Viewport / Platform Windows

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
    return io;
}

static void ImGuiDestroy()
{
	// Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

Window::Window(int width, int height, const char* title, FrameCallback callback)
: m_Width(width), m_Height(height), m_FrameCallback(callback)
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
	glfwDestroyWindow(this->Context());
}

void Window::CreateRenderContext()
{
	if (m_Renderer)
	{
		std::cout << "Resetting the renderer\n";
		m_Renderer.reset();
	}
	m_Renderer = std::make_unique<Renderer>(this, 2048);
}

void Window::Open()
{
	ImGuiIO& io = ImGuiInit(this->Context());
	std::cout << "Window is opening. Creating rendering context\n";

	CreateRenderContext();

	while (!glfwWindowShouldClose(m_Window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.11f, 0.11f, 0.12f, 1.0f);

		m_FrameCallback(this);

		// std::cout << "Render frame in Window\n";
		RenderContext()->Update();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// std::cout << "ImGui frame in Window\n";
		RenderContext()->ImGuiUpdate(io);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

		glViewport(0, 0, m_Width, m_Height);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, true);
}