#include <Application.h>
#include <Utility/Matrix.h>
#include <Utility/Vertex.h>

int main()
{	
	// We create a pointer with an application and run it immediately
	std::unique_ptr<Application> app = std::make_unique<Application>("Cartesian Plotter");
	app->SetVsync(true);
	app->Run(1920, 1000);
}
