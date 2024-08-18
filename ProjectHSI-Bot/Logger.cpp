/*!
\file ProjectHSI-Bot/Logger.cpp

\brief Defines various logging functions.

This file supplies the `ProjectHSI_Bot::CLogger` namespace and implements the informal CLogger standard.

\see ProjectHSI-Bot/Logger.hpp
*/

#include "Logger.hpp"
#include <chrono>
#include <cstdio>
#if defined(_MSC_VER)
#include <format>
#elif defined(__clang__)
#define LOGGER_TIME_NOT_SUPPORTED_ON_COMPILER_COMPILER_ID "Clang"
#pragma warning Time logging in Logger.cpp is not supported on the Clang compiler.
#elif defined(__GNUC__)
#define LOGGER_TIME_NOT_SUPPORTED_ON_COMPILER_COMPILER_ID "GCC"
#pragma warning Time logging in Logger.cpp is not supported on the GCC compiler.
#else
#define LOGGER_TIME_NOT_SUPPORTED_ON_COMPILER_COMPILER_ID "this compiler"
#pragma warning Time logging in Logger.cpp is not supported on this compiler.
#endif
#include <string>
#include <regex>
#include <cstdarg>
#include <vadefs.h>

//void ProjectHSI_Bot::CLogger::log(LogStruct &logStruct, std::string_view logMessage, const std::source_location logSource) {
	
//}

template<typename... Args>
void ProjectHSI_Bot::CLogger::log(const ProjectHSI_Bot::CLogger::LogStruct &logStruct, const std::string &logMessage, const std::string &logSource, Args... args);
