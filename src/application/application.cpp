#include "application/application.hpp"
#include "camera/camera.hpp"

Application::Application(const int& argc, char* argv[])
	: m_argc(argc)
	, m_argv(argv)
{
}

void Application::start()
{
	Camera camera;
	camera.open();
}

Application::~Application()
{
}
