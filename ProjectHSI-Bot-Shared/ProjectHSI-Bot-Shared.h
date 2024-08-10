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

	\note
		This function can really by anything it can have any return type, and any arguments.
		It's only requirements is that it exists and has C linkage (if compiling with a C++ compiler).

	\remarks
		Modules may need other dependencies than the defaults ProjectHSI-Bot needs and provides.
		To avoid accidentally loading a dependency as a regular module (and probably crashing the application in the process) this function's existence is checked for.
	*/
	void EXPORT projecthsi_bot_module_prescene();

	/*!
	\brief Used by the orchestrator to allow the module to check for ABI compatibility.
	 
	It is recommended to use the #ABI_CHECK macro to check the ABI version of the orchestrator, but the use of #ABI_CHECK is not required.
	 
	\warning You MUST NOT initialize anything in the abi_check function.
	Module initialization MUST be done in the respective, instead in the abi_check function.
	
	\note You MAY initalize certain ABI flags in your application with if you wish to use an implementation of this function other than the one provided by #ABI_CHECK
	
	\see ABI_CHECK
	\param[in] abiVersion The ABI version of the orchestrator.
	\returns A boolean representing if the module is compatible with the given ABI version. If this is false, the engine will unload the DLL and will the interface will not be initalized.
    */
	bool EXPORT abi_check(ProjectHSI_Bot_Shared_ABIVersion abiVersion);

	/*!
	\brief Pre-initalization routine.

	Do early pre-initalization routines that don't involve the orchestrator. Don't attempt to do bi-directional communication with the orchestrator here - do that in the ::init function.

	\returns The module information of the module - should be const, since the orchestrator will never modify this variable.
	*/
	const ProjectHSI_Bot_Shared_ModuleInformation EXPORT preinit();

	/*!
	\brief Initalization routine.

	\param[in] orchestratorFunctionPointers Various function pointers from the orchestrator. You should probably store these, as otherwise you'll have no way to communicate bi-directionally with the orchestrator.
	*/
	void EXPORT init(ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers orchestratorFunctionPointers);

	/*!
	\brief Post-initalization routine.

	Not theortically required (and in fact, not needed at all), but if you want to do something here, you can.
	*/
	void EXPORT postinit();

	/*!
	\brief Used by the orchestrator to tell the module to destroy itself.
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

\warning You must use this macro or reimplement ::projecthsi_bot_module_prescene (although reimplementing it is pointless, since the function will never be called).
*/
#define PROJECTHSI_BOT_MODULE_PRESCENE void EXPORT projecthsi_bot_module_prescene() {}