#include "SharedLibraryManagement.hpp"
#include "Interface/SharedLibraryManagement.hpp"

void ProjectHSI_Bot::Module::SharedLibraryManagement::loadModules() {
	ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::loadInterfaces();
}

void ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModules() {
	ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::unloadInterfaces();
}