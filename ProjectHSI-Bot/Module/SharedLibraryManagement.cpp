/*!
\file ProjectHSI-Bot/Module/SharedLibraryManagement.cpp

\brief This file implements the ProjectHSI_Bot::Module::SharedLibraryManagement namespace.

This module is a wrapper for Interfaces & Engine loading.

\see ProjectHSI-Bot/Module/SharedLibraryManagement.hpp
*/

#include "SharedLibraryManagement.hpp"
#include "Interface/SharedLibraryManagement.hpp"

void ProjectHSI_Bot::Module::SharedLibraryManagement::loadModules() {
	ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::loadInterfaces();
}

void ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModules() {
	ProjectHSI_Bot::Module::Interface::SharedLibraryManagement::unloadInterfaces();
}