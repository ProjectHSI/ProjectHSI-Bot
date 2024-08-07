/*!
\file ProjectHSI-Bot/Module/ABICheck.hpp

\brief This file supplies the `ProjectHSI_Bot::Module::ABICheck` namespace.

This module is used for checking the ABI Compatibility of a module.

\see ProjectHSI-Bot/Module/ABICheck.cpp
*/

#include <cstdint>
#include <ProjectHSI-Bot-Shared-Types.h>

namespace ProjectHSI_Bot {
	namespace Module {
		namespace ABICheck {
			/*!
			\brief This typedef is a type for a function pointer of type ::abi_check.
			*/
			typedef bool (*abi_check_funct)(ProjectHSI_Bot_Shared_ABIVersion) noexcept(false);

			/*!
			\brief Performs the ABI Check on a given module.

			This tests whether the module has the `abi_check` function, executes it, and outputs the result.

			\warning
			Note that this function does not perform an in-depth check on a given module - there may be further problems done the line if the module is not fully programmed to the ABI standard.
			You should be prepared to terminate the problem (via C++ exceptions) if the module doesn't have a function required for the ABI.

			\note
			Note that the `abi_check` function is allowed to return `true` for some modules which have special logic for differing Orchestrator ABI versions.
			This is why this function is structured this way - to allow for this behaviour.

			\param[in] moduleHandle The handle of the module returned by `SDL_LoadObject`.
			\returns Whether the module is compatible.
			*/
			uint_least8_t performAbiCheck(void *moduleHandle) noexcept(true);
		}
	}
}