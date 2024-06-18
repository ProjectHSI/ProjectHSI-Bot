#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

namespace ProjectHSI_Bot {
	namespace Socket {
#ifdef WIN32
		extern WSADATA WSADATAInstance;
#endif

		int Initalize();
		int Uninitalize();
	}
}