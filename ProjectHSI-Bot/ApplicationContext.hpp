#include <filesystem>
#include <string>

namespace ProjectHSI_Bot {
	namespace ApplicationContext {
		extern const char *basePathChar;
		extern const char *prefPathChar;
		extern std::string basePathString;
		extern std::string prefPathString;
		extern std::filesystem::path basePathPath;
		extern std::filesystem::path prefPathPath;

		void initalize();
		void terminate();
	}
}