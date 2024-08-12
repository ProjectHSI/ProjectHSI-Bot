#include "Version.hpp"
#include "BasicABIFunctions.hpp"
#include <functional>
#include <string>
#include "Logger.hpp"

ProjectHSI_Bot_Shared_ABIVersion ProjectHSI_Bot::Module::BasicABIFunctions::getOrchestratorAbiVersion() noexcept {
	return ProjectHSI_Bot_Shared_ABIVersion {ABI_VERSION_MAJOR, ABI_VERSION_MINOR, ABI_VERSION_PATCH};
}

ProjectHSI_Bot_Shared_SemanticVersion ProjectHSI_Bot::Module::BasicABIFunctions::getOrchestratorSemanticVersion() noexcept {
	return ProjectHSI_Bot::Version::abiFriendlyVersion;
}

std::function<void(const char*, ProjectHSI_Bot_Shared_CLogger_LogLevel)> ProjectHSI_Bot::Module::BasicABIFunctions::getLogLevelLogFunction(std::string moduleName) noexcept {
	return [moduleName](const char *log, ProjectHSI_Bot_Shared_CLogger_LogLevel logLevel) -> void {
		return ProjectHSI_Bot::CLogger::log(logLevel, log, moduleName);
	};
}

std::function<void(const char *, ProjectHSI_Bot_Shared_CLogger_LogStruct)> ProjectHSI_Bot::Module::BasicABIFunctions::getLogStructLogFunction(std::string moduleName) noexcept {
	return [moduleName](const char *log, ProjectHSI_Bot_Shared_CLogger_LogStruct logStruct) -> void {
		return ProjectHSI_Bot::CLogger::log(logStruct, log, moduleName);
	};
}