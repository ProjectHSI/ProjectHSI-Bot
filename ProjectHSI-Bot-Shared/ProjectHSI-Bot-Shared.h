/*!
\file ProjectHSI-Bot-Shared.h

\brief A C header file which contains declarations which are expected to be implemented or used in every module.
*/

#pragma once

#include "SO.h"
#include "ProjectHSI-Bot-Shared-Types.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*!
	\brief Used by the orchestrator to check if a shared object is even a ProjectHSI-Bot module.

	This function isn't expected to do anything and will never be called by the orchestrator. It's existence is checked for by the orchestrator, however.

	\warning This function must still be implemented. 

	\remarks
		Modules may need other dependencies than the defaults ProjectHSI-Bot needs and provides.
		To avoid accidentally loading a dependency as a regular module (and probably crashing the application in the process) this function's existence is checked for.
	*/
	void EXPORT projecthsi_bot_module_prescene();

	/*!
	\brief Used by the orchestrator to allow the module to check for ABI compatibility.
	 
	It is recommended to use the #ABI_CHECK macro to check the ABI version of the orchestrator, but the use of #ABI_CHECK is not required.
	 
	\warning You MUST NOT initalize the engine in the abi_check function.
	Engine initalization is done via a seperate (TBA) call, and the engine initalization MUST be done there, instead in the abi_check function.
	
	\note You MAY certain ABI flags in your application with if you wish to use an implementation of this function other than the one provided by #ABI_CHECK
	
	\see ABI_CHECK
	\param[in] abiVersion The ABI version of the orchestrator.
	\returns A boolean representing if the module is compatible with the given ABI version. If this is false, the engine will unload the DLL and will the interface will not be initalized.
    */
	bool EXPORT abi_check(ProjectHSI_Bot_Shared_ABIVersion abiVersion);

	/*!
	\brief Used by the orhcestrator to tell the module to initalize.

	\note Initalization must be done here, instead of in the abi_check function.

	\note There are module-type-specific initalization functions. Initalize those behaviours in those functions instead of here.

	\param[in] orchestratorFunctionPointers Various function pointers from the orchestrator. You should probably store these, as otherwise you'll have no way to communicate bi-directionally with the orchestrator.
	\returns The module information of the module - should be const, since the orchestrator will never modify this variable.
	*/
	const ProjectHSI_Bot_Shared_ModuleInformation EXPORT init(ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers orchestratorFunctionPointers);

	/*!
	\brief Used by the orchestrator to tell the module to destroy itself.

	\note There are module-type-specific destruction functions. Destroy those behaviours in those functions instead of here.
	*/
	void EXPORT destroy();

#ifdef __cplusplus
}
#endif

/*!
\brief Provides the recommended behaviour for the behaviour of ABI-version checking.

Custom modules may override the abi_check function to provide different behaviour for different ABI versions.
*/
#define ABI_CHECK bool EXPORT abi_check(ProjectHSI_Bot_Shared_ABIVersion abiVersion) { return (abiVersion.major == ABI_VERSION_MAJOR && abiVersion.minor == ABI_VERSION_MINOR && abiVersion.patch == ABI_VERSION_PATCH); }

/*!
\brief Provides a dummy implementation of projecthsi_bot_module_prescene.

\warning You must use this macro or reimplement ::projecthsi_bot_module_prescene (although reimplementing it is useless, since the function will never be called).
*/
#define PROJECTHSI_BOT_MODULE_PRESCENE void EXPORT projecthsi_bot_module_prescene() {}