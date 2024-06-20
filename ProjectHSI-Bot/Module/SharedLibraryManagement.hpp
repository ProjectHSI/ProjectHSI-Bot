/*!
\file ProjectHSI-Bot/Module/SharedLibraryManagement.hpp

\brief This file supplies the ProjectHSI_Bot::Module::SharedLibraryManagement namespace.

This module is a wrapper for Interfaces & Engine loading.

\see ProjectHSI-Bot/Module/SharedLibraryManagement.cpp
*/

namespace ProjectHSI_Bot {
	namespace Module {
		namespace SharedLibraryManagement {
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
		}
	}
}