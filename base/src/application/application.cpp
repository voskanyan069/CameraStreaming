#include <iostream>
#include <memory>

#include "application/application.hpp"
#include "application/cmd_argument.hpp"

Application::Application(const int argc, const char* argv[])
	: m_argc(argc)
	, m_argv(argv)
	, m_cmdargs(CMDArguments::instance())
{
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

Application::~Application()
{
}
