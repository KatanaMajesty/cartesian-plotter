#include <Core/Window.h>

std::unique_ptr<Window::KeyEvents> Window::m_Callbacks = std::make_unique<Window::KeyEvents>();

void Window::ParseKeyboardInput(GLFWwindow* context, int key, int scancode, int state, int mods)
{
	// States are GLFW_PRESS or GLFW_RELEASE in most cases
	// Keys are usually GLFW_KEY_W...A...S...D
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(context));
	Window::KeyEventsIterator iterator = m_Callbacks->find(key);
	if (iterator != m_Callbacks->end())
	{
		iterator->second(state, window);
	}
}

void Window::ParseWindowResize(GLFWwindow* context, int width, int height)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(context));
	Events::onWindowResize(width, height, window);
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
	glfwSetWindowUserPointer(m_Window, reinterpret_cast<void*>(this));
	glfwSetKeyCallback(m_Window, Window::ParseKeyboardInput);
	glfwSetWindowSizeCallback(m_Window, Window::ParseWindowResize);
}

void Window::RegisterKeyCallbacks()
{
	Window::RegisterCallback(GLFW_KEY_ESCAPE, Events::onWindowClose);
}

void Window::RegisterCallback(int key, std::function<bool(int, Window*)> function)
{
	std::cout << "Registering callback for key: " << key << std::endl;
	m_Callbacks->insert(std::make_pair(key, function));
}

void Window::CreateRenderContext()
{
	m_Renderer = std::make_unique<Renderer>(this, 2048);
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

		glViewport(0, 0, *m_Width, *m_Height);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, true);
}