#pragma once

#include <Core/Window.h>

/**
 * Application allows to create a window and register per-state keyboard callbacks (key events)
 * It also holds a Window object, that can be manipulated inside
 * 
 * Application acts as a buffer between the user, events and a Window object, thus incapsulating
 * GLFW and OpenGL context in Window
 * 
 * This class is also responsible for GLFW context and will delete it when destroyed
 */
class Application
{
public:
	// A mapping of (key, state) pair to the certain event.
    // This map is only used as a listener of key state changes, thus it will be called only once, and not once each frame
	using KeyEvents = std::unordered_map<std::pair<int, int>, std::function<bool(Window*)>>;
public:
	// Constructor will immediately initialize GLFW and setup OpenGL Hints
	Application(const char*, bool isVsync = true);
    // Destructor resets all GLFW callbacks and pointers. Also it terminates GLFW
	~Application();

	// Creates a Window class object
	void Run(int width, int height);
    inline bool IsVsync() const { return m_IsVsync; };
    inline void SetVsync(bool isVsync) { m_IsVsync = isVsync; };
    inline void SetSwapInterval(int isVsync) { glfwSwapInterval(isVsync); }
	// maps callbacks to the respective (key, state) pair
    void MapCallback(int key, int state, std::function<bool(Window*)>);
private:
	// Registers keyboard callbacks from unordered map
	void RegisterKeyCallbacks();
	// Functions Parse* are GLFW callbacks
    static void ParseMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void ParseKeyboardInput(GLFWwindow* context, int key, int scancode, int action, int mods);
	static void ParseWindowResize(GLFWwindow* context, int width, int height);
    static void ParseGLFWErrors(int error, const char* description);
private:
	const char* m_Title;
	std::unique_ptr<Window> m_Window;
	static KeyEvents m_KeyEventMap;
    bool m_IsVsync;
};

/**
 *  This structure is used in order for std::unordered_map to
 *  be able to hash keys correctly
 */
template<typename T, typename U> struct std::hash<std::pair<T, U>> 
{
    size_t operator() (const std::pair<T, U>& p) const 
    {
        // std::cout << "New hash!\n";
        auto h1 = std::hash<T>{}(p.first);
        auto h2 = std::hash<U>{}(p.second);

        // Only for demonstration purposes, i.e. works but is overly simple
        // E.g., every symmetric pair will hash to 0 and 
        // pairs that differ only by permutation will have the same hash

        // Rather use boost::hash_combine function
        return h1 ^ h2;
    }
};