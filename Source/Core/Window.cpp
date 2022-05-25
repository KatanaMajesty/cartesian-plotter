#include <Core/Window.h>
#include <Core/Events.h>

std::unique_ptr<Window::KeyEvents> Window::m_Callbacks = std::make_unique<Window::KeyEvents>();

void Window::ParseKeyboardInput(GLFWwindow* context, int key, int scancode, int state, int mods)
{
	// States are GLFW_PRESS or GLFW_RELEASE in most cases
	// Keys are usually GLFW_KEY_W...A...S...D
	Window::KeyEventsIterator iterator = m_Callbacks->find(key);
	if (iterator != m_Callbacks->end())
	{
		iterator->second(state, context);
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
	Window::RegisterCallback(GLFW_KEY_ESCAPE, [&](int state, GLFWwindow* context) -> bool {
		if (state == GLFW_PRESS)
		{
			Events::OnWindowShouldClose(context);
			glfwSetWindowShouldClose(context, true);
			return true;
		}
		return false;
	});
}

void Window::Open()
{
	RegisterKeyCallbacks();
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, true);
}

void Window::RegisterCallback(int key, std::function<bool(int, GLFWwindow*)> function)
{
	std::cout << "Registering callback for key: " << key << std::endl;
	m_Callbacks->insert(std::make_pair(key, function));
}