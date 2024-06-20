/*!
\file ProjectHSI-Bot/Module/Interface/SharedLibraryManagement.hpp

\brief This file supplies the ProjectHSI_Bot::Module::Interface::SharedLibraryManagement namespace.

This module is used for managing interfaces in the "modules/interfaces" folder, relative to the base path (ProjectHSI_Bot::ApplicationContext::basePathChar).

\see ProjectHSI-Bot/Module/Interface/SharedLibraryManagement.cpp
*/

namespace ProjectHSI_Bot {
	namespace Module {
		namespace Interface {
			namespace SharedLibraryManagement {
				/*!
				\brief Loads all interfaces in "modules/interfaces", relative to the base path (ProjectHSI_Bot::ApplicationContext::basePathChar).
				*/
				void loadInterfaces();

				/*!
				\brief Unloads all interfaces loaded by ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::loadInterfaces.
				*/
				void unloadInterfaces();
			}
		}
	}
}