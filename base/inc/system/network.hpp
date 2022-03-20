#ifndef __SYSTEM_NETWORK_HPP__
#define __SYSTEM_NETWORK_HPP__

#include <string>
#include <string.h>
#include <ifaddrs.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace sys
{

inline std::string _get_ip()
{
	struct ifaddrs* ifAddrStruct = NULL;
    struct ifaddrs* ifa = NULL;
    void* tmpAddrPtr = NULL;
	char* addressBuffer;
    getifaddrs(&ifAddrStruct);
    for (ifa = ifAddrStruct; NULL != ifa; ifa = ifa->ifa_next)
	{
        if (!ifa->ifa_addr) continue;
        if (AF_INET == ifa->ifa_addr->sa_family)
		{
            tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            addressBuffer = new char[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
        }
    }
    if (NULL != ifAddrStruct) freeifaddrs(ifAddrStruct);
	return addressBuffer;
}

inline void get_my_ip(std::string& ip)
{
	ip = _get_ip();
}

}

#endif // __SYSTEM_NETWORK_HPP__
