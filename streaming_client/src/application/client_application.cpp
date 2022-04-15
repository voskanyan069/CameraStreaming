#include <iostream>

#include "system/network.hpp"
#include "application/client_application.hpp"

ClientApplication::ClientApplication(const int argc, const char* argv[])
	: Application(argc, argv)
	, m_is_save(0)
{
}

void ClientApplication::add_options(po::options_description& desc)
{
	std::string my_ip;
	sys::get_my_ip(my_ip);
    desc.add_options()
        ("help,h", "produce help message")
        ("host,H", po::value<std::string>()->default_value(my_ip),
         "set hostname to connect")
        ("save-frames,S", po::bool_switch(&m_is_save),
         "enable/disable frames saving")
        ("port,P", po::value<int>()->default_value(13023),
         "port of the streaming server")
        ("path,p", po::value<std::string>()->default_value("./data/"),
         "path to save frames")
        ;
}

void ClientApplication::count_options(const po::variables_map& vm)
{
    push_bool("save_frames", m_is_save);
	if (vm.count("host"))
    {
        CMDStrArgument* arg = new CMDStrArgument(vm["host"].as<std::string>());
        push_argument("host", (ArgumentBase*)arg);
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

bool ClientApplication::parse_options()
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

ClientApplication::~ClientApplication()
{
}
