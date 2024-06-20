/*!
\file ProjectHSI-Bot/Module/ABICheck.cpp

\brief This file implements the `ProjectHSI_Bot::Module::ABICheck` namespace.

This module is used for checking the ABI Compatibility of a module.

\see ProjectHSI-Bot/Module/ABICheck.hpp
*/

#include "ABICheck.hpp"
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL.h>

/*!
\brief This typedef is a type for a function pointer of type ::abi_check.
*/
typedef bool (*abi_check_funct)(ProjectHSI_Bot_Shared_ABIVersion);

bool ProjectHSI_Bot::Module::ABICheck::performAbiCheck(void *moduleHandle) {
	abi_check_funct abi_check_func;

	abi_check_func = reinterpret_cast< abi_check_funct >(SDL_LoadFunction(moduleHandle, "abi_check"));

	bool abi_compatible = abi_check_func({0, 0, 1});

	return true;
}
