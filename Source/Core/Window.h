#pragma once

// Thirdparty & STD includes
#include <unordered_map>
#include <functional>

// Project Includes
#include <Event/Events.h>
#include <Core/Renderer.h>

/**
 * 	@brief Window represents and object, that holds Renderer, GLFWwindow and ImGui context.
 * 	This class also responsible for creating a @see @ref Renderer.
 * 
 * 	Although this Window holds ImGui context, it is not responsible for GLFW context,
 * 	where @see @ref Application class comes in handy
 * 
 * 	Class allows Event system to communicate with renderer and manage the window.
 * 
 * 	In order to get a Renderer @see Window::CreateRenderContext() method must be called.
 * 	This function will create a pointer to the Renderer object
 * 
 * 	Method Window::Open() creates a renderer and initializes ImGui. Right after that a GLFWwindow is opened.
 * 	Main-loop will start right after, where buffers will be swapped, events will be polled, glViewport will be handled,
 * 	as well as @see Renderer::Render() & @see Renderer::ImGuiRender() functions will be ran each frame
 */
class Window
{
public:
	// Constructor creates a GLFWwindow object of respective width, height and with respective title
	Window(int width, int height, const char* title);
	~Window();

	// Opens a GLFWwindow and start Main-loop. ImGui and Renderer context will be created beforehand
	void Open();
	// Closes the Window, although won't handle it's context destruction as well as it won't call any destructor
	void Close();
	void CreateRenderContext();

	inline GLFWwindow* Context() { return m_Window; }
	inline constexpr float AspectRatio() const { return static_cast<float>(m_Width) / m_Height; }
	inline void SetAspectRatio(int width, int height) { m_Width = width; m_Height = height; }
private:
	int m_Width;
	int m_Height;
	GLFWwindow* m_Window;
	std::unique_ptr<Renderer> m_Renderer;
};