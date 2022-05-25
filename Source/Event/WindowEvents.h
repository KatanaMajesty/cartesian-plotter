#pragma once

#include <GLFW/glfw3.h>
#include <Event/GenericEvents.h>

namespace Events
{
	class WindowShouldCloseEvent : public GenericKeyboardEvent
	{
	public:
		inline virtual bool Execute(int state, GLFWwindow* context) override
		{
			if (state == GLFW_PRESS)
			{
				std::cout << "Window will be closed now" << std::endl;
				glfwSetWindowShouldClose(context, true);
				return true;
			}
			return false;
		}
	};
};