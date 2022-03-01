#ifndef __APPLICATION_APPLICATION_HPP__
#define __APPLICATION_APPLICATION_HPP__

class Application
{
public:
	Application(const int& argc, char* argv[]);
	void start();
	~Application();

private:
	const int& m_argc;
	char** m_argv;
};

#endif // __APPLICATION_APPLICATION_HPP__
