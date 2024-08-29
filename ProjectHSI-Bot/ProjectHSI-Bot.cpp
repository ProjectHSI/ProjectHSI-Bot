// ProjectHSI-Bot.cpp : Defines the entry point for the application.
//

//#define SDL_MAIN_HANDLED
//#include <SDL.h>

#include "ApplicationContext.hpp"
#include "Module/SharedLibraryManagement.hpp"
#include "Version.hpp"

#include "Logger.hpp"
#include <iostream>

int main()
{
	ProjectHSI_Bot::ApplicationContext::initalize();

	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::TRACE, "Test");
	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::DEBUG, "Test");
	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::VERBOSE, "Test");
	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::INFORMATION, "Test");
	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::WARNING, "Test");
	ProjectHSI_Bot::CLogger::log(ProjectHSI_Bot::CLogger::LogLevel::ERROR, "Test");

	ProjectHSI_Bot::Module::SharedLibraryManagement::loadModules();
	ProjectHSI_Bot::Module::SharedLibraryManagement::unloadModules();

	ProjectHSI_Bot::ApplicationContext::destroy();

	return 0;
}