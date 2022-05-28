#include <Core/Application.h>
#include <Event/Events.h>

Application::Application(const char* title)
: m_Title(title)
{
	if (!glfwInit())
	{
		throw std::runtime_error("glfwInit");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Application::~Application()
{
	glfwTerminate();
}

void Application::Run(int width, int height)
{
	if (m_Window)
	{
		m_Window.reset();
	}
	m_Window = std::make_unique<Window>(width, height, m_Title);

	glfwSetWindowUserPointer(m_Window->Context(), reinterpret_cast<void*>(m_Window.get()));
	glfwSetKeyCallback(m_Window->Context(), Application::ParseKeyboardInput);
	glfwSetWindowSizeCallback(m_Window->Context(), Application::ParseWindowResize);

	RegisterKeyCallbacks();

	m_Window->Open();
}

void Application::RegisterKeyCallbacks()
{
	MapCallback(GLFW_KEY_ESCAPE, GLFW_PRESS, Events::onWindowClose);
}

void Application::MapCallback(int key, int state, std::function<bool(int, Window*)> function)
{
	std::cout << "Registering callback for key: " << key << std::endl;
	m_KeyEventMap->insert(std::make_pair(std::make_pair(key, state), function));
}

void Application::ParseWindowResize(GLFWwindow* context, int width, int height)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(context));
	Events::onWindowResize(width, height, window);
}

void Application::ParseKeyboardInput(GLFWwindow* context, int key, int scancode, int state, int mods)
{
	// States are GLFW_PRESS or GLFW_RELEASE in most cases
	// Keys are usually GLFW_KEY_W...A...S...D
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(context));
	Application::KeyEvents::const_iterator iterator = m_KeyEventMap->find(std::make_pair(key, state));
	if (iterator != m_KeyEventMap->end())
	{
		iterator->second(state, window);
	}
}

std::unique_ptr<Application::KeyEvents> Application::m_KeyEventMap = std::make_unique<Application::KeyEvents>();