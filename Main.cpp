#include <Core/Application.h>

int main()
{
	std::unique_ptr<Application> app = std::make_unique<Application>(1280, 720);
	app->Run();
}