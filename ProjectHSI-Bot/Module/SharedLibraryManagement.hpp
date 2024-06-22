/*!
\file ProjectHSI-Bot/Module/SharedLibraryManagement.hpp

\brief This file supplies the ProjectHSI_Bot::Module::SharedLibraryManagement namespace.

This module is a wrapper for Interfaces & Engine loading.

\see ProjectHSI-Bot/Module/SharedLibraryManagement.cpp
*/

#include <filesystem>

namespace ProjectHSI_Bot {
	namespace Module {
		namespace SharedLibraryManagement {
			/*!
			\brief The file extension of a shared object.

			This will be "dll" on Windows, and "so" in Unix.

			\note This is always shown as "so" in Doxygen. This is beacuse Doxygen does not define the `WIN32` macro which this variable relies on (even on Windows).
			This will update to the correct value on compilation.
			*/
		#ifdef WIN32
			constexpr const char *sharedObjectFileExtension("dll");
		#else
			constexpr const char *sharedObjectFileExtension("so");
		#endif

			/*!
			\brief Loads all modules. Loading behaviour is defined by the respective sub-functions this calls.

			\see ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::loadInterfaces
			*/
			void loadModules();

			/*!
			\brief Unloads all modules. Unloading behaviour is defined by the respective sub-functions this calls.

			\see ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::unloadInterfaces
			*/
			void unloadModules();

			/*!
			\brief Loads an module given the path to it.
			
			\warning The module handle returned may be nullptr. This will happen when the module could not be loaded for any reason.

			\param[in] modulePath The path to the shared object.
			\return A handle to module that was loaded.
			As described in the SDL2 documentation, the type of the handle is opaque to the application.
			*/
			void* loadModule(std::filesystem::path modulePath);

			/*!
			\brief Loads an module given the path to it.

			\note This function, unlike ProjectHSI_Bot::Module::SharedLibraryManagement::loadModule, will not fail (excluding catastrophic errors).

			\param[in] moduleHandle A handle to the module to be unloaded.
			*/
			void unloadModule(void* moduleHandle);

			/*!
			\brief This typedef is a type for a function pointer of type ::init.
			*/
			typedef void (*init_funct)();

			/*!
			\brief This typedef is a type for a function pointer of type ::destroy.
			*/
			typedef void (*destroy_funct)();
		}
	}
}