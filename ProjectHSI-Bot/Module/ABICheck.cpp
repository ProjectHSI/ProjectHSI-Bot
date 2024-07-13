/*!
\file ProjectHSI-Bot/Module/ABICheck.cpp

\brief This file implements the `ProjectHSI_Bot::Module::ABICheck` namespace.

This module is used for checking the ABI Compatibility of a module.

\see ProjectHSI-Bot/Module/ABICheck.hpp
*/

#include "../Logger.hpp"
#include "ABICheck.hpp"
#include <cstdint>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL_loadso.h>
#include <stdio.h>

uint_least8_t ProjectHSI_Bot::Module::ABICheck::performAbiCheck(void *moduleHandle) noexcept(true) {
	if (!SDL_LoadFunction(moduleHandle, "projecthsi_bot_module_prescene"))
		return 2;

	void *abi_check_func = SDL_LoadFunction(moduleHandle, "abi_check");

	if (!abi_check_func)
		return false;

	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, "Checking module ABI...");

	uint_least8_t abiCheckResult;

	try {
		abiCheckResult = static_cast< uint_least8_t >(!reinterpret_cast< ProjectHSI_Bot::Module::ABICheck::abi_check_funct >(abi_check_func)({ABI_VERSION_MAJOR, ABI_VERSION_MINOR, ABI_VERSION_PATCH}));
	} catch (...) {
		abiCheckResult = 1;
	}

	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, "Checked module ABI.");

	return abiCheckResult;
}
