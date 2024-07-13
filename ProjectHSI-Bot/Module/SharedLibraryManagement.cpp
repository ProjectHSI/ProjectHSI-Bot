/*!
\file ProjectHSI-Bot/Module/SharedLibraryManagement.cpp

\brief This file implements the ProjectHSI_Bot::Module::SharedLibraryManagement namespace.

This module is a wrapper for Interfaces & Engine loading.

\see ProjectHSI-Bot/Module/SharedLibraryManagement.hpp
*/

#include "../ApplicationContext.hpp"
#include "../Logger.hpp"
#include "ABICheck.hpp"
#include "Interface/SharedLibraryManagement.hpp"
#include "SharedLibraryManagement.hpp"
#include <array>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <format>
#include <functional>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL.h>
#include <stack>
#include <stdio.h>
#include <string>
#include <unordered_map> 
#include <utility>
#include <vector>

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

void ProjectHSI_Bot::Module::SharedLibraryManagement::loadModules() noexcept(true) {
	std::filesystem::path modulesPath = ProjectHSI_Bot::ApplicationContext::basePathPath.append("modules");

	if (std::filesystem::exists(modulesPath)) {
		for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(modulesPath)) {
			ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle moduleBundle = ProjectHSI_Bot::Module::SharedLibraryManagement::loadModule(entry.path());
			if (moduleBundle)
				modules.push_back(moduleBundle);
		}
	} else {
		fprintf(stderr, "The 'modules' directory doesn't exist. This means that no modules will be loaded. Press Control+C to exit the application on the prompt.\n");
	}
}

void ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModules() noexcept(true) {
	for (ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle _module : modules) {
		ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModule(_module);
	}

	modules.clear();
}

ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle ProjectHSI_Bot::Module::SharedLibraryManagement::loadModule(std::filesystem::path sharedObjectPath) noexcept(true) {
	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, std::format("Loading '{}'...", sharedObjectPath.filename().generic_string().c_str()));

	if (sharedObjectPath.extension() != (std::string(".") + std::string(ProjectHSI_Bot::Module::SharedLibraryManagement::sharedObjectFileExtension))) {
		ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, std::format("File '{}' is not a shared object (or doesn't have the '{}' extension). This file will be skipped.", sharedObjectPath.filename().generic_string().c_str(), sharedObjectFileExtension));

		return {};
	}

	void *sharedObjectHandle = SDL_LoadObject(sharedObjectPath.generic_string().c_str());

	// Win32 has it's own error messages for if a module fails to load, so we'll macro this out here.
	if (sharedObjectHandle == NULL) {
//	#ifndef WIN32
		ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::ERROR, std::format("Failed to load '{}' due to an error thrown by SDL. This may not be a valid shared object.\nThe error thrown is: {}", sharedObjectPath.filename().generic_string().c_str(), SDL_GetError()));
//	#endif

		//SDL_UnloadObject(sharedObjectHandle);
		return {};
	}

	switch (ProjectHSI_Bot::Module::ABICheck::performAbiCheck(sharedObjectHandle)) {
		case 1:
			ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::WARNING, std::format("Failed to load '%s' due to it's incompatibility with the current ABI version (%u.%u.%u).\n\n", sharedObjectPath.filename().generic_string().c_str(), ABI_VERSION_MAJOR, ABI_VERSION_MINOR, ABI_VERSION_PATCH));
			SDL_UnloadObject(sharedObjectHandle);
			return {};

		case 2:
			ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, std::format("Refusing to load '%s' as it is not a ProjectHSI-Bot module.", sharedObjectPath.filename().generic_string().c_str()));
			SDL_UnloadObject(sharedObjectHandle);
			return {};
	}

	void *init_func = SDL_LoadFunction(sharedObjectHandle, "init");

	if (!init_func) {
		ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, std::format("No initalization function found for '%s'.\n", sharedObjectPath.filename().generic_string().c_str()));
		SDL_UnloadObject(sharedObjectHandle);
		return {};
	}

	const ProjectHSI_Bot_Shared_ModuleInformation moduleInformation = reinterpret_cast< ProjectHSI_Bot::Module::SharedLibraryManagement::init_funct >(init_func)({});
	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::DEBUG, std::format("Module Identifier of '{}': '{}'.", sharedObjectPath.filename().generic_string().c_str(), moduleInformation.name));

	for (const ModuleTypeFunctionArrayEntry& moduleTypeFunctionMapEntry : moduleTypeFunctionArray) {
		if (moduleInformation.capabilities & moduleTypeFunctionMapEntry.andOperationOperand)
			moduleTypeFunctionMapEntry.moduleTypeFunction.first(sharedObjectHandle);
	}

	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, std::format("Loaded '{}'.", sharedObjectPath.filename().generic_string().c_str()));

	return { sharedObjectHandle, moduleInformation, sharedObjectPath };
}

void ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModule(ProjectHSI_Bot::Module::SharedLibraryManagement::ModuleBundle _module) noexcept(true) {
	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::WARNING, std::format("Unloading '%s'...", _module.sharedObjectPath.filename().generic_string().c_str()));

	for (const ModuleTypeFunctionArrayEntry& moduleTypeFunctionMapEntry : moduleTypeFunctionArray) {
		try {
			if (_module.moduleInformation.capabilities & moduleTypeFunctionMapEntry.andOperationOperand)
				moduleTypeFunctionMapEntry.moduleTypeFunction.second(_module.sharedObjectHandle);
		} catch (...) {
			ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::WARNING,
				std::format("Module '{}' is incompatible with the module type '%s' as an exception was thrown"
				"when the respective module type handler was called. This exception will be ignored since it is destroy-time for this object.", _module.sharedObjectPath.filename().generic_string().c_str(), moduleTypeFunctionMapEntry.moduleType));
		}
	}

	void *destroy_func = SDL_LoadFunction(_module.sharedObjectHandle, "destroy");
	
	if (destroy_func) {
		try {
			reinterpret_cast< ProjectHSI_Bot::Module::SharedLibraryManagement::destroy_funct >(destroy_func)();
		} catch (...) {
			ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::WARNING, std::format("No destruction function found for '{}'.", _module.sharedObjectPath.filename().generic_string().c_str()));
		}
	}

	SDL_UnloadObject(_module.sharedObjectHandle);

	log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, std::format("Unloaded '{}'.", _module.sharedObjectPath.filename().generic_string().c_str()));

	return;
}
