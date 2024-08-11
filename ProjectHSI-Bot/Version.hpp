#include <ProjectHSI-Bot-Shared-Types.h>
#include <string_view>

namespace ProjectHSI_Bot {
	namespace Version {
		constexpr struct {
			unsigned long long major {};
			unsigned long long minor {};
			unsigned long long patch {};

			std::string_view preRelease {};
			std::string_view buildId {};
		} standardVersion = {0, 0, 1, "alpha.1", ""};

		constexpr ProjectHSI_Bot_Shared_SemanticVersion abiFriendlyVersion = {
			standardVersion.major,
			standardVersion.minor,
			standardVersion.patch,
			standardVersion.preRelease.data(),
			standardVersion.buildId.data()
		};
	}
}