#include "HTTP.hpp"

#include <cstdint>
#include <map>
//#include <SDL_net.h>
#include <string>
#include <vector>

/*
void CreateHTTPRequest(TCPsocket& socket, std::string& path, std::string& host, std::map < std::string, std::string >& headers);
inline void CreateHTTPRequest(TCPsocket& socket, std::string& path, std::string& host) { CreateHTTPRequests(socket, path, host, {}); }

void CreateHTTPRequest(TCPsocket& socket, std::string& path, std::string& host, std::map < std::string, std::string >& headers, std::string data) {
	{
		std::string request = "";

		request += "GET " + path + "HTTP/1.1";
	}
	std::string response = "";
}
inline void CreateHTTPRequest(TCPsocket& socket, std::string& path, std::string& host, std::map < std::string, std::string >& headers, std::vector<uint8_t> data) { CreateHTTPRequests(socket, path, host, headers, std::string(reinterpret_cast<char*>(data.data()), data.size())); }
inline void CreateHTTPRequest(TCPsocket& socket, std::string& path, std::string& host, std::string data) { CreateHTTPRequests(socket, path, host, {}, std::string(reinterpret_cast<char*>(data.data()), data.size())); }
inline void CreateHTTPRequest(TCPsocket& socket, std::string& path, std::string& host, std::vector<uint8_t> data) { CreateHTTPRequests(socket, path, host, {}, std::string(reinterpret_cast<char*>(data.data()), data.size())); }
*/