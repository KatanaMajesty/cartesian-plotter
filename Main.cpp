#include <Core/Application.h>

/*
TODO:
- Fix 2+ Windows opened one after another with Application->Run()
*/

int main()
{
	// We create a pointer with an application and run it immediately
	std::unique_ptr<Application> app = std::make_unique<Application>("Cartesian Plotter");
	app->Run(1280, 720);
	// app->Run(1280, 720);
}