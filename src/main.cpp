#include "application/application.hpp"

int main(int argc, const char* argv[])
{
	Application app(argc, argv);
	int rc = app.start();
	return rc;
}
