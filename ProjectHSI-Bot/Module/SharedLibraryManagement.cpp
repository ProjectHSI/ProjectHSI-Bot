/*!
\file ProjectHSI-Bot/Module/SharedLibraryManagement.cpp

\brief This file implements the ProjectHSI_Bot::Module::SharedLibraryManagement namespace.

This module is a wrapper for Interfaces & Engine loading.

\see ProjectHSI-Bot/Module/SharedLibraryManagement.hpp
*/

#include "ABICheck.hpp"
#include "Interface/SharedLibraryManagement.hpp"
#include "SharedLibraryManagement.hpp"
#include <cstdio>
#include <filesystem>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL_loadso.h>

void ProjectHSI_Bot::Module::SharedLibraryManagement::loadModules() {
	ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::loadInterfaces();
}

void ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModules() {
	ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::unloadInterfaces();
}

void* ProjectHSI_Bot::Module::SharedLibraryManagement::loadModule(std::filesystem::path sharedObjectPath) {
	printf("Loading %s...\n", sharedObjectPath.filename().generic_string().c_str());

	if (sharedObjectPath.extension() != (std::string(".") + std::string(ProjectHSI_Bot::Module::SharedLibraryManagement::sharedObjectFileExtension))) {
		fprintf(stderr, "File %s is not a shared object (or doesn't have the '.%s' extension). This file will be skipped.\n", sharedObjectPath.filename().generic_string().c_str(), sharedObjectFileExtension);

		return nullptr;
	}

	void *sharedObjectHandle = SDL_LoadObject(sharedObjectPath.generic_string().c_str());

	// Win32 has it's own error messages for if a module fails to load, so we'll macro this out here.
	if (sharedObjectHandle == NULL) {
	//#ifndef WIN32
		printf("Failed to load %s due to an error thrown by SDL. This may not be a valid shared object.\nThe error thrown is: %s\n", sharedObjectPath.filename().generic_string().c_str(), SDL_GetError());
	//
		SDL_UnloadObject(sharedObjectHandle);
		return nullptr;
	}

	if (!ProjectHSI_Bot::Module::ABICheck::performAbiCheck(sharedObjectHandle)) {
		printf("Failed to load %s due to it's incompatibility with the current ABI version (%u.%u.%u).\n", sharedObjectPath.filename().generic_string().c_str(), ABI_VERSION_MAJOR, ABI_VERSION_MINOR, ABI_VERSION_PATCH);
		SDL_UnloadObject(sharedObjectHandle);
		return nullptr;
	}

	void *init_func = SDL_LoadFunction(sharedObjectHandle, "init");

	if (init_func)
		reinterpret_cast< ProjectHSI_Bot::Module::SharedLibraryManagement::init_funct >(init_func)();

	return sharedObjectHandle;
}

void ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModule(void *sharedObjectHandle) {

	void *destroy_func = SDL_LoadFunction(sharedObjectHandle, "destroy");

	if (destroy_func)
		reinterpret_cast< ProjectHSI_Bot::Module::SharedLibraryManagement::destroy_funct >(destroy_func)();

	SDL_UnloadObject(sharedObjectHandle);

	return;
}
