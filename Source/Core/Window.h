#pragma once

// Glew should be on top of GLFW
#include <unordered_map>
#include <functional>

#include <Event/Events.h>
#include <Core/Renderer.h>

// void GLFWKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)

class Window
{
public:
	using KeyEvents = std::unordered_map<int, std::function<bool(int, Window*)>>;
	using KeyEventsIterator = KeyEvents::const_iterator;
	
public:
	Window(int& width, int& height);
	~Window() = default;

	void Open();
	void Close();

	void RegisterKeyCallbacks();
	void CreateRenderContext();

	inline GLFWwindow* Context() { return m_Window; }
	inline constexpr float AspectRatio() const { return static_cast<float>(*m_Width) / *m_Height; }
	inline void SetAspectRatio(int width, int height) { *m_Width = width; *m_Height = height; }
private:
	void RegisterCallback(int key, std::function<bool(int, Window*)> function);

	static void ParseKeyboardInput(GLFWwindow* context, int key, int scancode, int action, int mods);
	static void ParseWindowResize(GLFWwindow* context, int width, int height);
private:
	int* m_Width;
	int* m_Height;
	GLFWwindow* m_Window;
	std::unique_ptr<Renderer> m_Renderer;

	// Key - keyboard code, Value - function that returns boolean and takes state of event (released/pressed)
	static std::unique_ptr<KeyEvents> m_Callbacks;
};