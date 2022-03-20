#include "application/server_application.hpp"
#include "camera/camera.hpp"

int main(int argc, const char* argv[])
{
	Application* app = new ServerApplication(argc, argv);
	if ( app->parse_options() )
	{
		return 1;
	}
	Camera camera;
	int rc = camera.open();
	return rc;
}
