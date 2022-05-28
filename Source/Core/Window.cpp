#include <Core/Window.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static ImGuiIO& ImGuiInit(GLFWwindow* context)
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
    return io;
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
	ImGuiIO& io = ImGuiInit(this->Context());
	CreateRenderContext();

	while (!glfwWindowShouldClose(m_Window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.11f, 0.11f, 0.12f, 1.0f);

		m_Renderer->Render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		m_Renderer->ImGuiRender();

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