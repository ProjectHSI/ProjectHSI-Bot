/*!
\file ProjectHSI-Bot/Logger.cpp

\brief Defines various logging functions.

This file supplies the `ProjectHSI_Bot::CLogger` namespace and implements the informal CLogger standard.

\see ProjectHSI-Bot/Logger.hpp
*/

#include "Logger.hpp"
#include <chrono>
#include <cstdio>
#include <format>
#include <string>

//void ProjectHSI_Bot::CLogger::log(LogStruct &logStruct, std::string_view logMessage, const std::source_location logSource) {
	
//}

void ProjectHSI_Bot::CLogger::log(const LogStruct &logStruct, std::string logMessage, std::string logSource) {
	// (ascii prefix) [(time)] [(source)] ((level)): (text)\n
	fprintf(
		logStruct.stderrRedirect ? stderr : stdout,
		"%s[%s] [%s] (%s): %s\n",
		logStruct.asciiPrefix.data(),
		std::format("{0:%c}", std::chrono::system_clock::now()).data(),
		logSource.data(),
		logStruct.logPrefix.data(),
		logMessage.data());
}
