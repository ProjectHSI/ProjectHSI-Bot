/*!
\file ProjectHSI-Bot/Module/Interface/SharedLibraryManagement.cpp

\brief This file supplies the `ProjectHSI_Bot::Module::Interface::SharedLibraryManagement` namespace.

This module is used for managing interfaces in the "modules/interfaces" folder, relative to the base path (ProjectHSI_Bot::ApplicationContext::basePathChar).

\see ProjectHSI-Bot/Module/Interface/SharedLibraryManagement.hpp
*/

#include "../../ApplicationContext.hpp"
#include "../ABICheck.hpp"
#include "../SharedLibraryManagement.hpp"
#include "SharedLibraryManagement.hpp"
#include <cstdio>
#include <filesystem>
#include <map>
#include <memory>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL.h>
#include <string>
#include <vector>

std::vector<void *> interfaceSharedObjects = std::vector<void *>();

void ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::loadInterfaces() {
	printf("Loading interfaces...\n");

	std::filesystem::path interfacesPath = ProjectHSI_Bot::ApplicationContext::basePathPath.append("modules/interfaces");

	if (std::filesystem::exists(interfacesPath)) {
		for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(interfacesPath)) {
			void *moduleHandle = ProjectHSI_Bot::Module::SharedLibraryManagement::loadModule(entry.path());

			if (moduleHandle != nullptr)
				interfaceSharedObjects.push_back(moduleHandle);
		}
	}

	printf("Finished loading interfaces.\n");
}

void ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::unloadInterfaces() {

}