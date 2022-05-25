#include <Core/Window.h>
#include <Event/WindowEvents.h>

std::unique_ptr<Window::KeyEvents> Window::m_Callbacks = std::make_unique<Window::KeyEvents>();

void Window::ParseKeyboardInput(GLFWwindow* context, int key, int scancode, int state, int mods)
{
	// States are GLFW_PRESS or GLFW_RELEASE in most cases
	// Keys are usually GLFW_KEY_W...A...S...D
	Window::KeyEventsIterator iterator = m_Callbacks->find(key);
	if (iterator != m_Callbacks->end())
	{
		iterator->second->Execute(state, context);
	}
}

Window::Window(int& width, int& height)
: m_Width(&width), m_Height(&height)
{
	m_Window = glfwCreateWindow(width, height, "Cartesian Plotter", nullptr, nullptr);
	if (!m_Window)
	{
		throw std::runtime_error("window is null");
	}

	glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("glew init");
	}

	glfwSetKeyCallback(m_Window, Window::ParseKeyboardInput);
}

void Window::RegisterKeyCallbacks()
{
	Window::RegisterCallback<Events::WindowShouldCloseEvent>(GLFW_KEY_ESCAPE);
}

void Window::CreateRenderContext()
{
	m_Renderer = std::make_unique<Renderer>();
}

void Window::Open()
{
	RegisterKeyCallbacks();

	CreateRenderContext();

	while (!glfwWindowShouldClose(m_Window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.11f, 0.11f, 0.12f, 1.0f);

		m_Renderer->Render();
		m_Renderer->ImGuiRender();

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, true);
}