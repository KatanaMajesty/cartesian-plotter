#pragma once

// Thirdparty & STD includes
#include <GLFW/glfw3.h>
#include <Core/Window.h>

class Window;    // TODO: Fix forward-declaration

/**
 * 	Namespace, that contains all related event functions
 */
namespace Events
{
	bool onWindowClose(int state, ::Window* window);
	bool onWindowResize(int width, int height, ::Window* window);
};