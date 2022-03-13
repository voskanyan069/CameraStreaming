#ifndef __APPLICATION_APPLICATION_HPP__
#define __APPLICATION_APPLICATION_HPP__

#include <boost/program_options.hpp>

#include "application/cmd_argument.hpp"

namespace po = boost::program_options;

class Application
{
public:
	Application(const int argc, const char* argv[]);
	int start();
	~Application();

private:
	void push_argument(const std::string& name, ArgumentBase* arg);
	void push_bool(const std::string& name, const bool arg);
	bool parse_options();
	void count_options(const po::variables_map& vm);
	void open_camera();

private:
	const int m_argc;
	const char** m_argv;
	CMDArguments& m_cmdargs;
};

#endif // __APPLICATION_APPLICATION_HPP__
