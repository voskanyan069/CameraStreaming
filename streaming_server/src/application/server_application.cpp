#include <iostream>

#include "application/server_application.hpp"

ServerApplication::ServerApplication(const int argc, const char* argv[])
	: Application(argc, argv)
	, m_is_save(0)
	, m_is_streaming(0)
{
}

void ServerApplication::add_options(po::options_description& desc)
{
    desc.add_options()
        ("help,h", "produce help message")
        ("device-id,D", po::value<int>()->default_value(0),
         "set device (camera) id")
        ("save-frames,S", po::bool_switch(&m_is_save),
         "enable/disable frames saving")
        ("streaming-mode,s", po::bool_switch(&m_is_streaming),
         "enable/disable camera streaming to clients")
        ("port,P", po::value<int>()->default_value(13023),
         "port for camera streaming server")
        ("path,p", po::value<std::string>()->default_value("./data/"),
         "path to save frames")
        ;
}

void ServerApplication::count_options(const po::variables_map& vm)
{
    push_bool("save_frames", m_is_save);
    push_bool("streaming_mode", m_is_streaming);
	if (vm.count("device-id"))
    {
        CMDIntArgument* arg = new CMDIntArgument(vm["device-id"].as<int>());
        push_argument("device_id", (ArgumentBase*)arg);
    }
    if (vm.count("port"))
    {
        CMDIntArgument* arg = new CMDIntArgument(vm["port"].as<int>());
        push_argument("port", (ArgumentBase*)arg);
    }
    if (vm.count("path"))
    {
        CMDStrArgument* arg = new CMDStrArgument(vm["path"].as<std::string>());
        push_argument("path", (ArgumentBase*)arg);
    }
}

bool ServerApplication::parse_options()
{
    po::options_description desc("Allowed options");
	add_options(desc);
    po::variables_map vm;
    po::store(po::parse_command_line(m_argc, m_argv, desc), vm);
    po::notify(vm);
    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }
    count_options(vm);
    return 0;
}

ServerApplication::~ServerApplication()
{
}
