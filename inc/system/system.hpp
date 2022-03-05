#ifndef __SYSTEM_SYSTEM_HPP__
#define __SYSTEM_SYSTEM_HPP__

#include <string>
#include <iostream>
#include <exception>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace sys
{

inline void create_directory(const std::string& path, bool create=false)
{
	if (fs::exists(path))
	{
		std::cout << "[NOTE] " << path << " already exists" << std::endl;
	}
	else
	{
		if (create)
		{
			std::cout << "[NOTE] Creating new directory: " << path << std::endl;
			fs::create_directory(path);
		}
		else
		{
			std::cout << "[NOTE] " << path << " already exists" << std::endl;
			throw std::runtime_error(path + " does not exist");
		}
	}
}

}

#endif // __SYSTEM_SYSTEM_HPP__
