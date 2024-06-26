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
	\brief Used by the orchestrator to allow the module to check for ABI compatibility.
	 
	It is recommended to use the #ABI_CHECK macro to check the ABI version of the orchestrator, but the use of #ABI_CHECK is not required.
	 
	\warning You MUST NOT initalize the engine in the abi_check function.
	Engine initalization is done via a seperate (TBA) call, and the engine initalization MUST be done there, instead in the abi_check function.
	
	\note You MAY certain ABI flags in your application with if you wish to use an implementation of this function other than the one provided by #ABI_CHECK
	
	\see ABI_CHECK
	\param[in] abiVersion The ABI version of the orchestrator.
	\returns A boolean representing if the module is compatible with the given ABI version. If this is false, the engine will unload the DLL and will the interface will not be initalized.
    */
	bool EXPORT abi_check(ProjectHSI_Bot_Shared_ABIVersion &abiVersion);

	/*!
	\brief Used by the orhcestrator to tell the module to initalize.

	\note Initalization must be done here, instead of in the abi_check function.

	\note There are module-type-specific initalization functions. Initalize those behaviours in those functions instead of here.

	\param[in] orchestratorFunctionPointers Various function pointers from the orchestrator. You should probably store these, as otherwise you'll have no way to communicate bi-directionally with the orchestrator.
	*/
	void EXPORT init(ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers &orchestratorFunctionPointers);

	/*!
	\brief Used by the orhcestrator to tell the module to destroy itself.

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