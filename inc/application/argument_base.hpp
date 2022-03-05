#ifndef __APPLICATION_ARGUMENT_BASE_HPP__
#define __APPLICATION_ARGUMENT_BASE_HPP__

template<typename T>
class CMDArgument;

class ArgumentBase
{
public:
    template <typename T> const T& get() const
	{
		//return dynamic_cast<const CMDArgument<T>&>(*this).get();
		return ((const CMDArgument<T>*)(this))->get();
	}

    //template<class T, class U> void set(const U& rhs)
	//{
	//	//return dynamic_cast<CMDArgument<T>&>(*this).set(rhs);
	//	return ((const CMDArgument<T>*)(this))->set();
	//}

    virtual ~ArgumentBase()
	{
	}
};

#endif // __APPLICATION_ARGUMENT_BASE_HPP__
