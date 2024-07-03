#include "BasicABIFunctions.hpp"
#include "../Version.hpp"

ProjectHSI_Bot_Shared_ABIVersion ProjectHSI_Bot::Module::BasicABIFunctions::getOrchestratorAbiVersion() noexcept {
	return ProjectHSI_Bot_Shared_ABIVersion {ABI_VERSION_MAJOR, ABI_VERSION_MINOR, ABI_VERSION_PATCH};
}

ProjectHSI_Bot_Shared_SemanticVersion ProjectHSI_Bot::Module::BasicABIFunctions::getOrchestratorSemanticVersion() noexcept {
	return ProjectHSI_Bot::Version::abiFriendlyVersion;
}
