#include <Core/Events.h>

namespace Events
{
	void OnWindowShouldClose(GLFWwindow* context)
	{
		std::cout << "Window will be closed now!" << std::endl;
	}
};
