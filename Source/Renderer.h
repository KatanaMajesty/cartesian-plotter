#pragma once

#include <unordered_map>
#include <vector>
#include <imgui.h>
#include <Core/Material.h>
#include <Core/Camera.h>
#include <Core/Object.h>

class Window;

/**
 * 	Renderer class represents a non-copyable object, that allows to render primitives, 
 * 	attach shaders and manipulate with Window object, it is bound to
 * 
 * 	Renderer is meant to be a developer-side class, where the main graphics are drawn
 * 	and OpenGL stuff is manipulated
 * 	
 * 	Renderer constructor takes in a Window object pointer and a number of maximum vertices in VBO.
 *  Maximum vertex amount is used in order to setup OpenGL state machine, e.g. VAO, VBO, shaders, etc.
 * 	OpenGL functions are also initialized in Renderer's constructor
 * 
 * 	Update() and ImGuiUpdate() methods are called each frame respectively in Window main loop
 * 
 * 	ObjectHandler is stored inside renderer. Every object, that handler contains, will be drawn
 * 	independently with a separate drawcall. If AABB should be rendered, there is extra drawcall for it
 * 	ObjectHandler is also responsible for Materials. They are stored in map and can be accessed via handler.
 * 	For more information about ObjectHandler @see @ref <Core/Object.h>
 * 
 * 	Renderer contains it's own camera. More information about camera at @see @ref <Core/Camera.h>
 */	
class Renderer
{
public:
	// Creates OpenGL bindings. This constructor is meant to be as a setup of rendering context
	// e.g. all VBOs, VAOs and Materials should be handler here
	Renderer(Window* const window, size_t vertices);

	// This object is non-copyable because OpenGL acts as a state machine,
	// thus more than one render context in one window is unsafe
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	// Destructor deletes VAO, VBO and clears all Materials
	~Renderer();

	// This two methods will be called each frame and should be used to render OpenGL graphics
	void Update();
	void ImGuiUpdate(ImGuiIO& io);

	// This function will render all data from ObjectHandler
	// renderCallback will be called each time the object is being rendered
	// renderCallback is called before glDrawArrays and after adding object vertices 
	// and calling Object::CallUniformCallback()
	void RenderDrawData(std::function<void(const Shader&)> renderCallback);

	// Getters and setters
	inline Window* const GetWindow() const { return m_Window; }
	inline Camera& GetCamera() { return m_Camera; }
	inline const Camera& GetCamera() const { return m_Camera; }
	inline ObjectHandler& GetObjectHandler() { return *m_ObjectHandler.get(); }
	inline const ObjectHandler& GetObjectHandler() const { return *m_ObjectHandler.get(); }
private:
	Window* const m_Window;
	
	Camera m_Camera;
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_Program;
	size_t m_Vertices;

	std::unique_ptr<ObjectHandler> m_ObjectHandler;
};