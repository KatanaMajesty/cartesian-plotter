#include <Core/Application.h>

Application::Application(int width, int height)
: m_Width(width), m_Height(height)
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

void Application::Run()
{
	m_Window = std::make_unique<Window>(m_Width, m_Height);
	m_Window->Open();
}