/*!
\file ProjectHSI-Bot/Module/BasicABIFunctions.hpp

\brief Defines some basic functions that don't really serve a purpose in the context of the ProjectHSI-Bot orchestrator by itself.

This file supplies the `ProjectHSI_Bot::Module::BasicABIFunctions` namespace.
These functions are expected to be used in the ::ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers struct.

\see ::ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers
\see ProjectHSI-Bot/Module/BasicABIFunctions.hpp
*/

#include <functional>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <string>
#include <cstdbool>

namespace ProjectHSI_Bot {
	namespace Module {
		namespace BasicABIFunctions {
			/*!
			\brief Returns the ABI version of the orchestrator.

			\returns The ABI version of the orchestrator.
			*/
			ProjectHSI_Bot_Shared_ABIVersion getOrchestratorAbiVersion() noexcept(true);

			/*!
			\brief Gets the semantic version of the orchestrator.

			\returns The semantic version of the orchestrator.
			*/
			ProjectHSI_Bot_Shared_SemanticVersion getOrchestratorSemanticVersion() noexcept(true);
			std::function<void(const char *, ProjectHSI_Bot_Shared_CLogger_LogLevel)> getLogLevelLogFunction(std::string moduleName) noexcept(true);
			std::function<void(const char *, ProjectHSI_Bot_Shared_CLogger_LogStruct)> getLogStructLogFunction(std::string moduleName) noexcept(true);
		}
	}
}