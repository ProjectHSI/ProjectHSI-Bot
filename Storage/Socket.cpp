#include "Socket.hpp"

#include <cstdio>

WSADATA ProjectHSI_Bot::Socket::WSADATAInstance{};

int ProjectHSI_Bot::Socket::Initalize() {
#ifdef WIN32
	int wsaStartupResult = WSAStartup(MAKEWORD(2, 2), &ProjectHSI_Bot::Socket::WSADATAInstance);

	if (wsaStartupResult != 0) {
		printf("WSAStartup failed: %d.\n", wsaStartupResult);
		return 1;
	}

	if (ProjectHSI_Bot::Socket::WSADATAInstance.wVersion) {

		
	}
#endif

	return 0;
}

int ProjectHSI_Bot::Socket::Uninitalize() {
#ifdef WIN32
	WSACleanup();
#endif

	

	return 0;
}
