#pragma once

// Glew should be on top of GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <functional>

class Window
{
public:
	using KeyEvents = std::unordered_map<int, std::function<bool(int, GLFWwindow*)>>;
	using KeyEventsIterator = KeyEvents::const_iterator;
public:
	Window(int& width, int& height);
	~Window() = default;

	void Open();
	void Close();

	static void Register_Callback(int key, std::function<bool(int, GLFWwindow*)>);
private:
	static void Parse_Keyboard_Input(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	int* m_Width;
	int* m_Height;
	GLFWwindow* m_Window;

	// Key - keyboard code, Value - function that returns boolean and takes state of event (released/pressed)
	static std::unique_ptr<KeyEvents> m_Callbacks;
};