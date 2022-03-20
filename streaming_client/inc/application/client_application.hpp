#ifndef __APPLICATION_CLIENT_APPLICATION_HPP__
#define __APPLICATION_CLIENT_APPLICATION_HPP__

#include <boost/program_options.hpp>

#include "application/application.hpp"
#include "application/cmd_argument.hpp"

namespace po = boost::program_options;

class ClientApplication : virtual public Application
{
public:
	ClientApplication(int argc, const char* argv[]);
	bool parse_options() override;
	virtual ~ClientApplication();

protected:
	void add_options(po::options_description& desc) override;
	void count_options(const po::variables_map& vm) override;

private:
	bool m_is_save;
};

#endif // __APPLICATION_CLIENT_APPLICATION_HPP__
