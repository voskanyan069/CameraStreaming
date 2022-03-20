#include "application/client_application.hpp"
#include "camera/viewer.hpp"

int main(int argc, const char* argv[])
{
	Application* app = new ClientApplication(argc, argv);
	if ( app->parse_options() )
	{
		return 1;
	}
	CameraViewer viewer;
	viewer.listen();
	return 0;
}
