#pragma once

#include <unordered_map>
#include <Renderer.h>
#include <Core/Events.h>

/**
 * @brief Window represents and object, that holds Renderer, GLFWwindow and ImGui context
 * 
 * Although this Window holds ImGui context, it is not responsible for GLFW context,
 * which Application is about
 * 
 * Class allows Event system to communicate with renderer and manage the window
 * 
 * Open() method is responsible for creating ImGui and Renderer context
 * Main loop is began right after all context creations
 * 
 * Constructor takes in width, height and title of GLFWwindow, as well as FrameCallback,
 * which is Events::OnFrameUpdate() function by default. Last will be called each frame
 * before Renderer::Update() and Renderer::ImGuiUpdate() methods
 * It should be used to parse keyboard input, for example, for translating camera
 * 
 * Window destructor destroys GLFWwindow and ImGui context
 */
class Window
{
public:
	// Frame callback is a function, that will be called before Renderer::Update() method
	// It is used in order to parse per-frame keyboard's key states
	// Default frame callback is Events::OnFrameUpdate() function
	using FrameCallback = std::function<bool(Window* window)>;
public:
	// Constructor creates a GLFWwindow object of respective width, height and title
	Window(int width, int height, const char* title, FrameCallback callback = Events::OnFrameUpdate);
	~Window();

	// Opens a GLFWwindow and starts the main loop. ImGui and Renderer context will be created beforehand
	void Open();
	// Closes the Window, although won't handle it's context destruction as well as it won't call any destructor
	void Close();

	// Getters and setters
	inline GLFWwindow* Context() { return m_Window; }
	inline const GLFWwindow* Context() const { return m_Window; }
	inline constexpr float Width() const { return static_cast<float>(m_Width); }
	inline constexpr float Height() const { return static_cast<float>(m_Height); }
	inline constexpr float AspectRatio() const { return static_cast<float>(m_Width) / m_Height; }
	inline void SetWidth(int width) { m_Width = width; }
	inline void SetHeight(int height) { m_Height = height; }
	inline Renderer* RenderContext() { return m_Renderer.get(); }
	inline const Renderer* RenderContext() const { return m_Renderer.get(); }
private:
	void CreateRenderContext();
private:
	int m_Width;
	int m_Height;
	GLFWwindow* m_Window;
	std::unique_ptr<Renderer> m_Renderer;
	FrameCallback m_FrameCallback;
};