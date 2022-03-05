#include <memory>

#include <boost/program_options.hpp>

#include "application/application.hpp"
#include "application/cmd_argument.hpp"
#include "camera/camera.hpp"

namespace po = boost::program_options;

Application::Application(const int& argc, const char* argv[])
	: m_argc(argc)
	, m_argv(argv)
	, m_cmdargs(CMDArguments::instance())
{
}

void Application::open_camera()
{
	Camera camera;
	camera.open();
}

void Application::push_argument(const std::string& name, ArgumentBase* arg)
{
	m_cmdargs.arguments[name] = arg;
}

bool Application::parse_options()
{
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("device-id,D", po::value<int>()->default_value(0), "set device (camera) id")
		("save-frames,S", po::value<bool>()->default_value(1), "enable/disable frames saving")
		("path,p", po::value<std::string>()->default_value("./data/"), "path to save frames")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(m_argc, m_argv, desc), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}
	if (vm.count("device-id"))
	{
		CMDArgument<int>* arg = new CMDArgument<int>(vm["device-id"].as<int>());
		push_argument("device_id", (ArgumentBase*)arg);
	}
	if (vm.count("save-frames"))
	{
		CMDArgument<bool>* arg = new CMDArgument<bool>(
				vm["save-frames"].as<bool>());
		push_argument("save_frames", (ArgumentBase*)arg);
	}
	if (vm.count("path"))
	{
		CMDArgument<std::string>* arg = new CMDArgument<std::string>(
				vm["path"].as<std::string>());
		push_argument("path", (ArgumentBase*)arg);
	}
	return 0;
}

int Application::start()
{
	if ( parse_options() )
	{
		return 1;
	}
	open_camera();
	return 0;
}

Application::~Application()
{
}
