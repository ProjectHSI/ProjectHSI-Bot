/*!
\file ProjectHSI-Bot/Module/BasicABIFunctions.hpp

\brief Defines some basic functions that don't really serve a purpose in the context of the ProjectHSI-Bot orchestrator by itself.

These functions are expected to be used in the ::ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers struct.

\see ::ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers
*/

#include <ProjectHSI-Bot-Shared-Types.h>

namespace ProjectHSI_Bot {
	namespace Module {
		namespace BasicABIFunction {
			/*!
			\brief Returns the ABI version of the orchestrator.

			\returns The ABI version of the orchestrator.
			*/
			ProjectHSI_Bot_Shared_ABIVersion getOrchestratorAbiVersion();

			/*!
			\brief Gets the semantic version of the orchestrator.

			\returns The semantic version of the orchestrator.
			*/
			ProjectHSI_Bot_Shared_SemanticVersion getOrchestratorSemanticVersion();
		}
	}
}