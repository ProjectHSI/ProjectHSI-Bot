#include "ABICheck.hpp"
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL.h>

typedef bool (*abi_check_funct)(ProjectHSI_Bot_Shared_ABIVersion);

bool ProjectHSI_Bot::Module::ABI_Check::performAbiCheck(void *moduleHandle) {
	abi_check_funct abi_check_func;

	abi_check_func = reinterpret_cast< abi_check_funct >(SDL_LoadFunction(moduleHandle, "abi_check"));

	bool abi_compatible = abi_check_func({0, 0, 1});

	return true;
}
