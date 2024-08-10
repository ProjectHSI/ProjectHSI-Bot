/*!
\file ProjectHSI-Bot-Shared-Interface.h

\brief This C header file contains declarations expected to be used in every interface module.
*/

#pragma once

#include "ProjectHSI-Bot-Shared-Interface-Types.h"
#include "ProjectHSI-Bot-Shared.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*!
	\brief Used by the orchestrator to signal to the module to initalize a specified interface.

	This is called in a watchdog thread - the destroy method will always be called if the event loop function.

	\note interfaceId is determined by the application, and thus if this is NULL-terminated, it will be NULL-terminated.
	*/
	void EXPORT init_interface(const char *interfaceId);

	/*!
	\brief Used by the orchestrator to signal to the module to start a specified interface.

	\note Don't destroy or create any resources here - instead, use the resources created in ::init_interface, it will always be called first.

	\note Erroring here will not cause problems with memory leaking - the watchdog will call ::destroy_interface even if this function errors.

	\note interfaceId is determined by the application, and thus if this is NULL-terminated, it will be NULL-terminated.
	*/
	void EXPORT interface_entry(const char *interfaceId);

	/*!
	\brief Used by the orchestrator to signal to the module to destroy a specified interface.

	This is called in a watchdog thread - the destroy method will always be called if the event loop function.

	\note interfaceId is determined by the application, and thus if this is NULL-terminated, it will be NULL-terminated.
	*/
	void EXPORT destroy_interface(const char *interfaceId);

#ifdef __cplusplus
}
#endif