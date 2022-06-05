#include <Application.h>

int main()
{
	// We create a pointer with an application and run it immediately
	std::unique_ptr<Application> app = std::make_unique<Application>("Cartesian Plotter");
	app->SetVsync(true);
	app->Run(1920, 1000);
}

/*
ADDED:
- Axis-Aligned Bounding Box (AABB) implementation
- ImGui user interface to manipulate non-sealed objects and materials
- Vertex structure (OpenGL vertex wrapper)
- Object class, that allows to conveniently add vertices to renderer
- Object handler, for easy object handling in renderer 
- Sealable objects, that cannot be modified at runtime
- Ability to select non-sealed objects at runtime
- Each object now contains AABB, which can be rendered if Object::RenderAABB() is true
- Objects now may implement collision AABB tests
- Materials were added. They are simply a (Shader, renderMode) pair wrappers
- Simple 2D camera with AABB, render borders and culling
- UUIDv4 generation (simplified)
- Vsync parameter in Application class
- Application::MapCallback() method is now public
- Application now is able to parse GLFW errors
- Window FrameCallback. More info in Window.h
IMPROVED:
- Vertex, AABB and UUID structures were added to project's Utility folder
- Doxygen comments were rewritten
- Removed keyboard main events from Application::KeyEvents to Window::FrameCallback (Events::OnFrameUpdate function)
- Vsync option added to Application
- Window::SetAspectRatio() replaced with Window::SetWidth() and Window::SetHeight()
- Renderer is non-copyable now
- Massive Renderer refactor, including changes in method names
- Shader class now uses std::string, which cannot be changed externally
- Moved Events namespace to Core folder, added new events
- More includes in precompiled header
REMOVED:
- Line, Triangle and Quad primitives
- Dynamic batching in renderer
FIXED:
- Window being created more than once occured an error
*/