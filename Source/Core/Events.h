#pragma once

class Window;
class Shader;
class Object;

/**
 * 	Namespace, that contains all related event functions
 */
namespace Events
{
	bool OnWindowClose(Window* window);
	bool OnKeyLeft	(Window* window);
	bool OnKeyRight (Window* window);
	bool OnKeyUp	(Window* window);
	bool OnKeyDown	(Window* window);
	bool OnWindowResize(int width, int height, Window* window);
	bool OnMouseScroll(double xoffset, double yoffset, Window* window);
	bool OnGLFWError(int error, const char* description);
	bool OnObjectRender(const Shader&, Object&);
	bool OnFrameUpdate(Window* window);
};