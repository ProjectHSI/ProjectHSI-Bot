#include <vector>
#include <mutex>
namespace ProjectHSI_Bot {
	namespace EventLoop {
		extern std::vector<std::vector<ProjectHSI_Bot_Shared_Event>> queuedEvents {};
		extern std::mutex queuedEventsMutex {};
	}
}