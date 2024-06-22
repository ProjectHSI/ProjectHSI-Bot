/*!
\file ProjectHSI-Bot/Module/ABICheck.cpp

\brief This file implements the `ProjectHSI_Bot::Module::ABICheck` namespace.

This module is used for checking the ABI Compatibility of a module.

\see ProjectHSI-Bot/Module/ABICheck.hpp
*/

#include "ABICheck.hpp"
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL_loadso.h>

bool ProjectHSI_Bot::Module::ABICheck::performAbiCheck(void *moduleHandle) {
	void *abi_check_func = SDL_LoadFunction(moduleHandle, "abi_check");

	if (!abi_check_func)
		return false;

	return reinterpret_cast< ProjectHSI_Bot::Module::ABICheck::abi_check_funct >(abi_check_func)({ABI_VERSION_MAJOR, ABI_VERSION_MINOR, ABI_VERSION_PATCH});
}
