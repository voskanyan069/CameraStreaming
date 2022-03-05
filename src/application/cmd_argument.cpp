#include "application/cmd_argument.hpp"

CMDArguments::CMDArguments()
{
}

CMDArguments& CMDArguments::instance()
{
	static CMDArguments INSTANCE;
	return INSTANCE;
}

CMDArguments::~CMDArguments()
{
}
