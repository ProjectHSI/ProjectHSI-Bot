#include "SharedLibraryManagement.hpp"
#include "../../ApplicationContext.hpp"
#include <ProjectHSI-Bot-Shared-Types.h>
#include <cstdio>
#include <filesystem>
#include <map>
#include <memory>
#include <SDL.h>
#include <string>

#ifdef WIN32
constexpr const char *sharedObjectFileExtension("dll");
#else
constexpr const char *sharedObjectFileExtension("so");
#endif

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
		goto emergen_stop;
	}

	typedef bool(*abi_check_funct)(ProjectHSI_Bot_Shared_ABIVersion);

	abi_check_funct abi_check_func;

	abi_check_func = static_cast<abi_check_funct>(SDL_LoadFunction(object, "abi_check"));

	abi_check_func({0, 0, 1});

emergen_stop:
	if (object)
		SDL_UnloadObject(object);
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