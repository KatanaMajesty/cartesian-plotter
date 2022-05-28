#pragma once

// Project Includes
#include <Core/Window.h>
#include <Core/Renderer.h>

/**
 * 	This structure is used in order for std::unordered_map to
 *  be able to hash keys correctly
 */
struct PairHash {
    template <class T1, class T2>
    size_t operator() (const std::pair<T1,T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Only for demonstration purposes, i.e. works but is overly simple
        // E.g., every symmetric pair will hash to 0 and 
        // pairs that differ only by permutation will have the same hash

        // Rather use boost::hash_combine function
        return h1 ^ h2;  
    }
};

/**
 * 	Application is a class that connects Window (which containts OpenGL context)
 * 	and Event System, thus allowing them to communicate with each other.
 * 
 * 	Event system is represented as a simple callback map bound to <keyboard key, state> keys.
 * 	This map is bound using GLFW to different window context events with methods that
 * 	start from "Parse" in its name
 * 
 * 	GLFWwindow context is stored inside Window class @see @ref Window class
 * 
 * 	Constructor takes in const char*, which represents Window Title
 * 
 * 	Method Run() creates a pointer on an object of @see @ref Window class,
 * 	sets all necessary callbacks, registers them and opens the window at the end.
 * 	glfwSetWindowUserPointer() function is also used when Run() method is called, so that Event system is able to receive
 * 	Window object during GLFW callback
 */
class Application
{
public:
	// Event map
	using KeyEvents = std::unordered_map<std::pair<int, int>, std::function<bool(int, Window*)>, PairHash>;
public:
	// Constructor will immediately initialize GLFW and setup OpenGL Hints
	Application(const char*);
	~Application();

	// Creates a Window class object
	void Run(int width, int height);
	// Registers keyboard callbacks from unordered map
	void RegisterKeyCallbacks();
private:
	// maps (inserts into unordered map) callbacks to the respective key and it's state
	void   MapCallback(int key, int state, std::function<bool(int, Window*)>);
	// Two functions ParseKeyboardInput & ParseWindowResize are GLFW callbacks
	// Their names speak for themselves
	static void ParseKeyboardInput(GLFWwindow* context, int key, int scancode, int action, int mods);
	static void ParseWindowResize(GLFWwindow* context, int width, int height);
private:
	const char* m_Title;
	std::unique_ptr<Window> m_Window;
	static std::unique_ptr<KeyEvents> m_KeyEventMap;
};