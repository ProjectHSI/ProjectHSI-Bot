/*!
\file ProjectHSI-Bot/Module/Interface/SharedLibraryManagement.cpp

\brief This file supplies the `ProjectHSI_Bot::Module::Interface::SharedLibraryManagement` namespace.

This module is used for managing interfaces in the "modules/interfaces" folder, relative to the base path (ProjectHSI_Bot::ApplicationContext::basePathChar).

\see ProjectHSI-Bot/Module/Interface/SharedLibraryManagement.hpp
*/

#include "../../ApplicationContext.hpp"
#include "../ABICheck.hpp"
#include "SharedLibraryManagement.hpp"
#include <cstdio>
#include <filesystem>
#include <map>
#include <memory>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL.h>
#include <string>

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
\brief Loads an interface given the path to it.

This loads the interface into the interfaces vector, so there is no return value.

\param[in] interfaceSharedObjectPath The path to the shared object.
*/
static void loadInterface(const std::filesystem::path &interfaceSharedObjectPath) {
	printf("Loading %s...\n", interfaceSharedObjectPath.filename().generic_string().c_str());

	if (interfaceSharedObjectPath.extension() != (std::string(".") + std::string(sharedObjectFileExtension))) {
		fprintf(stderr, "File %s is not a shared object (or doesn't have the '.%s' extension). This file will be skipped.\n", interfaceSharedObjectPath.filename().generic_string().c_str(), sharedObjectFileExtension);

		return;
	}

	void* object = SDL_LoadObject(interfaceSharedObjectPath.generic_string().c_str());

// Win32 has it's own error messages for if a module fails to load, so we'll macro this out here.
	if (object == NULL) {
	#ifndef WIN32
		printf("Failed to load %s due to an error thrown by SDL. This may not be a valid shared object.\nThe error thrown is: %s\n", interfaceSharedObjectPath.filename().generic_string().c_str(), SDL_GetError());
	#endif
		SDL_UnloadObject(object);
	}

	if (!ProjectHSI_Bot::Module::ABICheck::performAbiCheck(object))
		SDL_UnloadObject(object);
	else {
		
	}
}

void ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::loadInterfaces() {
	printf("Loading interfaces...\n");

	std::filesystem::path interfacesPath = ProjectHSI_Bot::ApplicationContext::basePathPath.append("modules/interfaces");

	if (std::filesystem::exists(interfacesPath)) {
		for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(interfacesPath)) {
			loadInterface(entry.path());
		}
	}

	printf("Finished loading interfaces.\n");
}

void ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::unloadInterfaces() {

}