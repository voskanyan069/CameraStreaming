#include <iostream>
#include <memory>

#include "application/application.hpp"
#include "application/cmd_argument.hpp"
#include "camera/camera.hpp"

Application::Application(const int argc, const char* argv[])
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

void Application::push_bool(const std::string& name, const bool arg)
{
	CMDArgument<bool>* argument = new CMDArgument<bool>(arg);
	push_argument(name, (ArgumentBase*)argument);
}

void Application::count_options(const po::variables_map& vm)
{
	if (vm.count("device-id"))
	{
		CMDArgument<int>* arg = new CMDArgument<int>(vm["device-id"].as<int>());
		push_argument("device_id", (ArgumentBase*)arg);
	}
	if (vm.count("port"))
	{
		CMDArgument<int>* arg = new CMDArgument<int>(
				vm["port"].as<int>());
		push_argument("port", (ArgumentBase*)arg);
	}
	if (vm.count("path"))
	{
		CMDArgument<std::string>* arg = new CMDArgument<std::string>(
				vm["path"].as<std::string>());
		push_argument("path", (ArgumentBase*)arg);
	}
}

bool Application::parse_options()
{
	bool is_save = 0;
	bool is_streaming = 0;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("device-id,D", po::value<int>()->default_value(0),
		 "set device (camera) id")
		("save-frames,S", po::bool_switch(&is_save),
		 "enable/disable frames saving")
		("streaming-mode,s", po::bool_switch(&is_streaming),
		 "enable/disable camera streaming to clients")
		("port,P", po::value<int>()->default_value(57606),
		 "port for camera streaming server")
		("path,p", po::value<std::string>()->default_value("./data/"),
		 "path to save frames")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(m_argc, m_argv, desc), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	push_bool("save_frames", is_save);
	push_bool("streaming_mode", is_streaming);
	count_options(vm);

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
