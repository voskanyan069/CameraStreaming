#ifndef __APPLICATION_ARGUMENT_BASE_HPP__
#define __APPLICATION_ARGUMENT_BASE_HPP__

template<typename T>
class CMDArgument;

class ArgumentBase
{
public:
    template <typename T> const T& get() const
	{
		return ((const CMDArgument<T>*)(this))->get();
	}

    virtual ~ArgumentBase()
	{
	}
};

#endif // __APPLICATION_ARGUMENT_BASE_HPP__
