#include <Event/Events.h>
#include <Core/Window.h>

namespace Events
{
	bool onWindowClose(int state, Window* window)
	{		
		window->Close();
		return true;
	}

	bool onWindowResize(int width, int height, Window* window)
	{
		window->SetAspectRatio(width, height);
		return false;
	}
};

