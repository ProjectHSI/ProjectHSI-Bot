#pragma once

#include "ProjectHSI-Bot-Shared-Types.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * \brief Used by the orchestrator to allow the engine/interface to check for ABI compatibility.
	 * 
	 * It is recommended to use the #ABI_CHECK macro to check the ABI version of the orchestrator, but the use of #ABI_CHECK is not required.
	 * 
	 * You **MUST NOT** initalize the engine in the abi_check function.
	 * Engine initalization is done via a seperate (TBA) call, and the engine initalization MUST be done there,
	 * instead in the abi_check function.
	 * 
	 * \see ABI_CHECK
	 * \param[in] abiVersion The ABI version of the orchestrator.
	 * \returns A boolean representing if the engine/interface is compatible with the given ABI version. If this is false, the engine will unload the DLL and will the interface will not be initalized.
     */
	bool __declspec(dllexport) abi_check(ProjectHSI_Bot_Shared_ABIVersion abiVersion);

#ifdef __cplusplus
}
#endif

/**
 * \brief Provides the recommended behaviour for the behaviour of ABI-version checking.
 * 
 * Custom libraries may override the abi_check function to provide different behaviour for different ABI versions.
 */
#define ABI_CHECK bool abi_check(ABIVersion abiVersion) { return (abiVersion.x == ABI_VERSION_X && abiVersion.y == ABI_VERSION_Y && abiVersion.z == ABI_VERSION_Z); }