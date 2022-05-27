#include <Event/Events.h>
#include <Core/Window.h>

namespace Events
{
	bool onWindowClose(int state, Window* window)
	{
		if (state == GLFW_PRESS)
		{
			std::cout << "Window will be closed now" << std::endl;
			glfwSetWindowShouldClose(window->Context(), true);
			return true;
		}
		return false;
	}

	bool onWindowResize(int width, int height, Window* window)
	{
		window->SetAspectRatio(width, height);
		return false;
	}
};

