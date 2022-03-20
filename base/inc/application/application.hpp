#ifndef __APPLICATION_APPLICATION_HPP__
#define __APPLICATION_APPLICATION_HPP__

#include <boost/program_options.hpp>

#include "application/cmd_argument.hpp"

namespace po = boost::program_options;

class Application
{
public:
	Application(const int argc, const char* argv[]);
	virtual bool parse_options() = 0;
	virtual ~Application();

protected:
	virtual void add_options(po::options_description& desc) = 0;
	virtual void count_options(const po::variables_map& vm) = 0;

	void push_argument(const std::string& name, ArgumentBase* arg);
	void push_bool(const std::string& name, const bool arg);

protected:
	const int m_argc;
	const char** m_argv;

private:
	CMDArguments& m_cmdargs;
};

#endif // __APPLICATION_APPLICATION_HPP__
