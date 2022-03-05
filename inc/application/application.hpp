#ifndef __APPLICATION_APPLICATION_HPP__
#define __APPLICATION_APPLICATION_HPP__

#include "application/cmd_argument.hpp"

class Application
{
public:
	Application(const int& argc, const char* argv[]);
	int start();
	~Application();

private:
	void push_argument(const std::string& name, ArgumentBase* arg);
	bool parse_options();
	void open_camera();

private:
	const int& m_argc;
	const char** m_argv;
	CMDArguments& m_cmdargs;
};

#endif // __APPLICATION_APPLICATION_HPP__
