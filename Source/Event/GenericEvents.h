#pragma once

#include <GLFW/glfw3.h>

class GenericEvent
{
public:
	GenericEvent() = default;
	~GenericEvent() = default;

	virtual bool Execute() = 0;
};

class GenericKeyboardEvent
{
public:
	GenericKeyboardEvent() = default;
	~GenericKeyboardEvent() = default;

	virtual bool Execute(int state, GLFWwindow* context) = 0;
};