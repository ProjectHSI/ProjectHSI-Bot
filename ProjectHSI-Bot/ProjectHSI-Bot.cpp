﻿// ProjectHSI-Bot.cpp : Defines the entry point for the application.
//

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "ApplicationContext.hpp"
#include "Module/SharedLibraryManagement.hpp"
#include "Version.hpp"

#include "Logger.hpp"

int main()
{
	ProjectHSI_Bot::ApplicationContext::initalize();

	ProjectHSI_Bot::Module::SharedLibraryManagement::loadModules();
	ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModules();

	ProjectHSI_Bot::ApplicationContext::destroy();

	return 0;
}