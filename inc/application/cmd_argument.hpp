#ifndef __APPLICATION_CMD_ARGUMENT_HPP__
#define __APPLICATION_CMD_ARGUMENT_HPP__

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "application/argument_base.hpp"

template <typename T>
class CMDArgument : ArgumentBase
{
public:
	CMDArgument(const T& rhs) : m_value(rhs) {}
	const T& get() const { return m_value; }
	//void set(const T& rhs) { m_value = rhs; }

private:
	const T m_value;
};

class CMDArguments
{
public:
	static CMDArguments& instance();

	CMDArguments(const CMDArguments&) = delete;
	CMDArguments& operator=(const CMDArguments&) = delete;

private:
	CMDArguments();
	~CMDArguments();

public:
	std::map<std::string, ArgumentBase*> arguments;
	std::vector<ArgumentBase*> args;
};

#endif // __APPLICATION_CMD_ARGUMENT_HPP__
