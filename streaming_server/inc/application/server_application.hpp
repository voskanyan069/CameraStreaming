#ifndef __APPLICATION_SERVER_APPLICATION_HPP__
#define __APPLICATION_SERVER_APPLICATION_HPP__

#include <boost/program_options.hpp>

#include "application/application.hpp"
#include "application/cmd_argument.hpp"

namespace po = boost::program_options;

class ServerApplication : virtual public Application
{
	typedef CMDArgument<std::string> CMDStrArgument;
	typedef CMDArgument<int> 		 CMDIntArgument;

public:
	ServerApplication(int argc, const char* argv[]);
	bool parse_options() override;
	virtual ~ServerApplication();

protected:
	void add_options(po::options_description& desc) override;
	void count_options(const po::variables_map& vm) override;

private:
	bool m_is_save;
	bool m_is_streaming;
};

#endif // __APPLICATION_SERVER_APPLICATION_HPP__
