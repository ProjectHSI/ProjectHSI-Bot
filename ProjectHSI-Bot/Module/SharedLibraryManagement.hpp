/*!
\file ProjectHSI-Bot/Module/SharedLibraryManagement.hpp

\brief This file supplies the ProjectHSI_Bot::Module::SharedLibraryManagement namespace.

This module is a wrapper for Interfaces & Engine loading.

\see ProjectHSI-Bot/Module/SharedLibraryManagement.cpp
*/

#include <filesystem>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <stdexcept>
#include <string>

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
			void loadModules() noexcept(true);

			/*!
			\brief Unloads all modules. Unloading behaviour is defined by the respective sub-functions this calls.

			\see ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::unloadInterfaces
			*/
			void unloadModules() noexcept(true);

		#pragma region ModuleBundle
			/*!
			\brief The list of module types.
			*/
			enum ModuleType {
				Engine,
				Interface,
				Board
			};
			
			/*!
			\brief This enum describes the module status at a specific time, see #ModuleBundle.moduleStatus.

			This is a bit mask. Use the & operation.

			\note The order of these enums are specific - their order describes the loading process.
			*/
			enum ModuleStatus {
				/*!
				\brief The module's shared object representation has been loaded.
				*/
				LOADED        = 0b1,

				/*!
				\brief The module has been verified to be an actual module (see #projecthsi_bot_module_prescene)
				*/
				MODULE_VERIFY = 0b10,

				/*!
				\brief The module has been verified to work with the current ProjectHSI-Bot ABI version.
				*/
				ABI_VERIFY = 0b100,

				/*!
				\brief The module has completed pre-initalization.

				When pre-initalization has been completed, the module information has been discovered and can be used.

				See #preinit.
				*/
				PRE_INIT = 0b1000,

				/*!
				\brief The module has completed initalization. The generic initalization phase has been completed and the module is ready to be used.

				See #init.

				\note The #postinit may be called after this flag is set, however the #postinit function does nothing of importance from the orchestrator's side, so this doesn't matter.
				*/
				INIT = 0b10000
			};

			/*!
			\brief A commonly used struct for passing around a module.
			*/
			class ModuleBundle {
			private:
				/*!
				\brief A pointer to the shared object behind the module.

				The value of this handle is opaque to the application as defined in SDL_LoadObject.
				*/
				void *sharedObjectHandle;

				/*!
				\brief Information about the module.
				
				\see ::ProjectHSI_Bot_Shared_ModuleInformation
				*/
				ProjectHSI_Bot_Shared_ModuleInformation moduleInformation {};

				/*!
				\brief A module status consisting of enum values from #ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleStatus
				*/
				unsigned long long moduleStatus = 0;

				/*!
				\brief The path of the module.
				*/
				std::filesystem::path sharedObjectPath;

				/*!
				\brief The function pointers provided to the module.
				*/
				ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers functionPointers;

				void generateFunctions() const;

			public:
			#pragma region Casts
				/*!
				\brief Returns the handle of the shared object this struct points to.

				\throws std::logic_error Thrown if the shared object this ModuleBundle refers to hasn't been loaded yet. see sharedObjectLoaded() to see if the shared object has been loaded.

				\see sharedObjectHandle
				*/
				operator void *() const noexcept(false) {
					if (!sharedObjectHandle)
						throw std::logic_error("Shared object not yet loaded.");

					return sharedObjectHandle;
				}

				/*!
				\brief Returns whether the shared object has been loaded.

				\returns Whether the shared object has been loaded yet.
				*/
				bool sharedObjectLoaded() const noexcept(true) {
					return sharedObjectHandle != nullptr;
				}

				/*!
				\brief Returns the path of the shared object this struct points to.

				\see sharedObjectHandle
				*/
				operator std::filesystem::path() const {
					return sharedObjectPath;
				}

				/*!
				\brief Returns the ::ProjectHSI_Bot_Shared_ModuleInformation the module reported during initalization.

				\throws std::logic_error If the module information hasn't been discovered yet.

				\see moduleInformation
				\see ::ProjectHSI_Bot_Shared_ModuleInformation
				*/
				operator ProjectHSI_Bot_Shared_ModuleInformation() const {
					if (!sharedObjectHandle)
						throw std::logic_error("Module information not yet discovered.");

					return moduleInformation;
				}

				unsigned long long getModuleStatus() const {
					return moduleStatus;
				}
			#pragma endregion

				/*!
				\brief Initalizes a moduleType from that module.
				*/
				void initalizeModuleTypeOfModule(ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleType moduleType) const;

				/*!
				\brief Initalizes a module based on the std::filesystem::path.

				This is the recommended way of initalizing the ModuleBundle.
				*/
				ModuleBundle(std::filesystem::path path);

				/*!
				\brief Initalizes a module from a std::string.
				*/
				inline ModuleBundle(std::string path) { ModuleBundle(std::filesystem::path(path)); }

				/*!
				\brief Initalizes a module from a const char *.
				*/
				inline ModuleBundle(const char *path) { ModuleBundle(std::filesystem::path(path)); }

				void operator+() const;
			};
		#pragma endregion

			/*!
			\brief Loads an module given the path to it.
			
			\warning The module handle returned may be nullptr. This will happen when the module could not be loaded for any reason.

			\param[in] modulePath The path to the shared object.
			\return A handle to module that was loaded.
			As described in the SDL2 documentation, the type of the handle is opaque to the application.
			*/
			//ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle loadModule(std::filesystem::path modulePath) noexcept(true);

			/*!
			\brief Loads an module given the path to it.

			\note This function, unlike ProjectHSI_Bot::Module::SharedLibraryManagement::loadModule, will not fail (excluding catastrophic errors).

			\param[in] (moduleHandle A handle to the module to be unloaded.)
			*/
			//void unloadModule(ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle _module) noexcept(true);

			/*!
			\brief This typedef is a type for a function pointer of type ::init.
			*/
			typedef ProjectHSI_Bot_Shared_ModuleInformation (*init_funct)(ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers) noexcept(false);

			/*!
			\brief This typedef is a type for a function pointer of type ::destroy.
			*/
			typedef void (*destroy_funct)() noexcept(false);
		}
	}
}