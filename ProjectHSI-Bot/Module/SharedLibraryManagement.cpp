/*!
\file ProjectHSI-Bot/Module/SharedLibraryManagement.cpp

\brief This file implements the ProjectHSI_Bot::Module::SharedLibraryManagement namespace.

This module is a wrapper for Interfaces & Engine loading.

\see ProjectHSI-Bot/Module/SharedLibraryManagement.hpp
*/

#include "../ApplicationContext.hpp"
#include "ABICheck.hpp"
#include "Interface/SharedLibraryManagement.hpp"
#include "SharedLibraryManagement.hpp"
#include <array>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <unordered_map> 
#include <utility>
#include <vector>
#include <stack>

static void nullModuleTypeFunc(void *_) {}

static void noImplementationNullmoduleTypeFunc(void *_) { }

//typedef std::function<void(void *)> ModuleTypeFunction;
typedef void (*ModuleTypeFunction)(void *);

struct ModuleTypeFunctionArrayEntry {
	int andOperationOperand;

	const char *moduleType;

	std::pair<ModuleTypeFunction, ModuleTypeFunction> moduleTypeFunction;
};

constexpr static std::array<ModuleTypeFunctionArrayEntry, 3> moduleTypeFunctionArray = {{
	{ProjectHSI_Bot_Shared_ModuleInformation_Capabilities_Engine, "engine", {nullModuleTypeFunc, noImplementationNullmoduleTypeFunc}},
	{ProjectHSI_Bot_Shared_ModuleInformation_Capabilities_Interface, "interface", {nullModuleTypeFunc, noImplementationNullmoduleTypeFunc}},
	{ProjectHSI_Bot_Shared_ModuleInformation_Capabilities_Board, "board", {nullModuleTypeFunc, noImplementationNullmoduleTypeFunc}}
}};

//static std::stack<int> t {};

static std::vector<ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle> modules {};

void ProjectHSI_Bot::Module::SharedLibraryManagement::loadModules() {
	std::filesystem::path modulesPath = ProjectHSI_Bot::ApplicationContext::basePathPath.append("modules");

	if (std::filesystem::exists(modulesPath)) {
		for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(modulesPath)) {
			ProjectHSI_Bot::Module::SharedLibraryManagement::loadModule(entry.path());
		}
	}
}

void ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModules() {
	for (ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle _module : modules) {
		ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModule(_module);
	}

	modules.clear();
}

ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle ProjectHSI_Bot::Module::SharedLibraryManagement::loadModule(std::filesystem::path sharedObjectPath) noexcept(true) {
	printf("\nLoading '%s'...\n", sharedObjectPath.filename().generic_string().c_str());

	if (sharedObjectPath.extension() != (std::string(".") + std::string(ProjectHSI_Bot::Module::SharedLibraryManagement::sharedObjectFileExtension))) {
		fprintf(stderr, "File %s is not a shared object (or doesn't have the '.%s' extension). This file will be skipped.\n\n", sharedObjectPath.filename().generic_string().c_str(), sharedObjectFileExtension);

		return {};
	}

	void *sharedObjectHandle = SDL_LoadObject(sharedObjectPath.generic_string().c_str());

	// Win32 has it's own error messages for if a module fails to load, so we'll macro this out here.
	if (sharedObjectHandle == NULL) {
	#ifndef WIN32
		printf("Failed to load %s due to an error thrown by SDL. This may not be a valid shared object.\nThe error thrown is: %s\n\n", sharedObjectPath.filename().generic_string().c_str(), SDL_GetError());
	#endif

		//SDL_UnloadObject(sharedObjectHandle);
		return {};
	}

	switch (ProjectHSI_Bot::Module::ABICheck::performAbiCheck(sharedObjectHandle)) {
		case 1:
			printf("Failed to load %s due to it's incompatibility with the current ABI version (%u.%u.%u).\n\n", sharedObjectPath.filename().generic_string().c_str(), ABI_VERSION_MAJOR, ABI_VERSION_MINOR, ABI_VERSION_PATCH);
			SDL_UnloadObject(sharedObjectHandle);
			return {};

		case 2:
			printf("Failed to load %s as it is not a ProjectHSI-Bot module.\n\n", sharedObjectPath.filename().generic_string().c_str());
			SDL_UnloadObject(sharedObjectHandle);
			return {};
	}

	void *init_func = SDL_LoadFunction(sharedObjectHandle, "init");

	if (!init_func) {
		printf("No initalization function found for '%s'.\n\n", sharedObjectPath.filename().generic_string().c_str());
		SDL_UnloadObject(sharedObjectHandle);
		return {};
	}

	const ProjectHSI_Bot_Shared_ModuleInformation moduleInformation = reinterpret_cast< ProjectHSI_Bot::Module::SharedLibraryManagement::init_funct >(init_func)({});

	printf("Module Identifier of '%s': '%s'\n", sharedObjectPath.filename().generic_string().c_str(), moduleInformation.name);

	for (ModuleTypeFunctionArrayEntry moduleTypeFunctionMapEntry : moduleTypeFunctionArray) {
		if (moduleInformation.capabilities & moduleTypeFunctionMapEntry.andOperationOperand)
			moduleTypeFunctionMapEntry.moduleTypeFunction.first(sharedObjectHandle);
	}

	printf("Loaded '%s'.\n", sharedObjectPath.filename().generic_string().c_str());

	return { sharedObjectHandle, moduleInformation, sharedObjectPath };
}

void ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModule(ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle _module) noexcept(true) {
	printf("\nUnloading '%s'...\n", _module.sharedObjectPath.filename().generic_string().c_str());

	for (ModuleTypeFunctionArrayEntry moduleTypeFunctionMapEntry : moduleTypeFunctionArray) {
		try {
			if (_module.moduleInformation.capabilities & moduleTypeFunctionMapEntry.andOperationOperand)
				moduleTypeFunctionMapEntry.moduleTypeFunction.second(_module.sharedObjectHandle);
		} catch (...) {
			printf(
				"Module '%s' is incompatible with the module type '%s' as an exception was thrown"
				"when the respective module type handler was called. This exception will be ignored since it is destroy-time for this object.", _module.sharedObjectPath.filename().generic_string().c_str(), moduleTypeFunctionMapEntry.moduleType);
		}
	}

	void *destroy_func = SDL_LoadFunction(_module.sharedObjectHandle, "destroy");
	
	if (destroy_func) {
		try {
			reinterpret_cast< ProjectHSI_Bot::Module::SharedLibraryManagement::destroy_funct >(destroy_func)();
		} catch (...) {
			printf("No destruction function found for '%s'.\n", _module.sharedObjectPath.filename().generic_string().c_str());
		}
	}

	SDL_UnloadObject(_module.sharedObjectHandle);

	printf("Unloaded '%s'.\n\n", _module.sharedObjectPath.filename().generic_string().c_str());

	return;
}
