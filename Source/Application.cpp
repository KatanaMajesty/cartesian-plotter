#include <Application.h>
#include <Core/Events.h>

Application::Application(const char* title, bool isVsync)
: m_Title(title), m_IsVsync(isVsync)
{
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Application::~Application()
{
	glfwSetWindowUserPointer(m_Window->Context(), nullptr);
	glfwSetKeyCallback(m_Window->Context(), NULL);
	glfwSetWindowSizeCallback(m_Window->Context(), NULL);
	glfwSetScrollCallback(m_Window->Context(), NULL);
	glfwSetErrorCallback(NULL);

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
	glfwSetScrollCallback(m_Window->Context(), Application::ParseMouseScroll);
	glfwSetErrorCallback(Application::ParseGLFWErrors);

	SetSwapInterval(this->IsVsync());

	RegisterKeyCallbacks();

	std::cout << "Successfully registered KeyEvent callbacks. Opening a window\n";

	m_Window->Open();
}

// TODO: Rewrite from state to stateFlags (bitmask)
void Application::RegisterKeyCallbacks()
{
	MapCallback(GLFW_KEY_ESCAPE, GLFW_PRESS, Events::OnWindowClose);
}

void Application::MapCallback(int key, int state, std::function<bool(Window*)> function)
{
	std::cout << "Registering callback for GLFW key: " << key << ". State: " << state << std::endl;
	m_KeyEventMap.insert(std::make_pair(std::make_pair(key, state), function));
}

void Application::ParseMouseScroll(GLFWwindow* context, double xoffset, double yoffset)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(context));
	Events::OnMouseScroll(xoffset, yoffset, window);
}

void Application::ParseWindowResize(GLFWwindow* context, int width, int height)
{
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(context));
	Events::OnWindowResize(width, height, window);
}

void Application::ParseKeyboardInput(GLFWwindow* context, int key, int scancode, int state, int mods)
{
	// States are GLFW_PRESS or GLFW_RELEASE in most cases
	// Keys are usually GLFW_KEY_W...A...S...D
	Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(context));
	Application::KeyEvents::const_iterator iterator = m_KeyEventMap.find(std::make_pair(key, state));
	if (iterator != m_KeyEventMap.end())
	{
		iterator->second(window);
	}
}

void Application::ParseGLFWErrors(int error, const char* description)
{
    Events::OnGLFWError(error, description);
}


Application::KeyEvents Application::m_KeyEventMap = Application::KeyEvents();