#ifndef __SYSTEM_DATE_HPP__
#define __SYSTEM_DATE_HPP__

#include <ctime>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

namespace sys
{

inline void get_date(std::string &date)
{
	using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);
    std::ostringstream oss;
    oss << std::put_time(&bt, "%Y-%m-%d_%H-%M-%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    date = oss.str();
}

}

#endif // __SYSTEM_DATE_HPP__
