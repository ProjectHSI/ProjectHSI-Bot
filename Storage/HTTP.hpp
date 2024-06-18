#include <cstdint>
#include <map>
//#include <SDL_net.h>
#include <string>
#include <vector>

inline void CreateHTTPRequest(int socket, std::string& path, std::string& host, std::map < std::string, std::string >& headers);
inline void CreateHTTPRequest(int socket, std::string& path, std::string& host);

inline void CreateHTTPRequest(int socket, std::string& path, std::string& host, std::map < std::string, std::string >& headers, std::string data);
inline void CreateHTTPRequest(int socket, std::string& path, std::string& host, std::map < std::string, std::string >& headers, std::vector<uint8_t> data);
inline void CreateHTTPRequest(int socket, std::string& path, std::string& host, std::string data);
inline void CreateHTTPRequest(int socket, std::string& path, std::string& host, std::vector<uint8_t> data);