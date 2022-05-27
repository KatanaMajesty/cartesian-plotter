#pragma once

#include <GLFW/glfw3.h>

class Window;

namespace Events
{
	bool onWindowClose(int state, Window* window);
	bool onWindowResize(int width, int height, Window* window);
};