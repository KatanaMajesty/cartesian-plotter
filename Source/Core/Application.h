#pragma once

#include <Core/Window.h>

class Application
{
public:
	Application(int width, int height);
	~Application();

	void Run();
private:
	int m_Width;
	int m_Height;
	std::unique_ptr<Window> m_Window;
};