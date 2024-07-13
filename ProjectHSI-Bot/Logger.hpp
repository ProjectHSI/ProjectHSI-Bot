/*!
\file ProjectHSI-Bot/Logger.hpp

\brief Defines various logging functions.

This file supplies the `ProjectHSI_Bot::CLogger` namespace and implements the informal CLogger standard.

\see ProjectHSI-Bot/Logger.cpp
*/

#pragma once

#include <cstdint>
#include <format>
#include <map>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <source_location>
#include <string>

namespace ProjectHSI_Bot {
	namespace CLogger {
		/*!
		\brief Log level struct used by CLogger, for easier use interally.

		You probably won't need this, the log levels in ::ProjectHSI_Bot::CLogger::LogLevel should do fine.
		Internally, the log levels in ::ProjectHSI_Bot::CLogger::LogLevel map to this struct. See the definitions in ProjectHSI-Bot/Logger.hpp.
		*/
		struct LogStruct {
			/*!
			\brief Visibility setting of the log level. Used to determine whether thee log level should be printed to the console.
			*/
			uint_least16_t logLevel;

			/*!
			\brief The prefix of the log level, which will be in brackets to identify it.
			*/
			std::string logPrefix;

			/*!
			\brief A prefix which is added to the beginning of the entire log.

			This property is expected to be used for ASCII text docorations to make logs identifiable. This is a standard string and no special rules apply.
			*/
			std::string asciiPrefix;

			/*!
			\brief If set to true, will direct the log to stderr instead of stdout.
			*/
			bool stderrRedirect;

			/*!
			\brief Constructs a ::ProjectHSI_Bot::CLogger::LogStruct.
			*/
			LogStruct(uint_least8_t logLevel, std::string logPrefix, std::string asciiPrefix, bool stderrRedirect) {
				this->logLevel = logLevel;
				this->logPrefix = logPrefix;
				this->asciiPrefix = asciiPrefix;
				this->stderrRedirect = stderrRedirect;
			}

			/*!
			\brief Constructs a ::ProjectHSI_Bot::CLogger::LogStruct, but with the logLevel being a standard int rather than a uint8_least8_t
			*/
			LogStruct(int logLevel, std::string logPrefix, std::string asciiPrefix, bool stderrRedirect) {
				this->logLevel = static_cast<uint_least8_t>(logLevel % UINT_LEAST8_MAX);
				this->logPrefix = logPrefix;
				this->asciiPrefix = asciiPrefix;
				this->stderrRedirect = stderrRedirect;
			}

			/*!
			\brief Constructs a ::ProjectHSI_Bot::CLogger::LogStruct from a ::ProjectHSI_Bot_Shared_CLogger_LogStruct.
			*/
			LogStruct(ProjectHSI_Bot_Shared_CLogger_LogStruct moduleLogStruct) {
				this->logLevel = moduleLogStruct.logLevel;
				this->logPrefix = std::string(moduleLogStruct.logPrefix);
				this->asciiPrefix = std::string(moduleLogStruct.asciiPrefix);
				this->stderrRedirect = moduleLogStruct.stderrRedirect;
			}
		};

		/*!
		\brief Log levels used by CLogger, for easier use internally.

		The log levels here map to ::ProjectHSI_Bot::CLogger::LogStruct
		\see ::ProjectHSI_Bot::CLogger::LogStruct
		*/
		enum LogLevel : uint_least8_t {
			ERROR,
			WARNING,
			INFORMATION,
			VERBOSE,
			DEBUG,
			TRACE
		};

		const std::map<LogLevel, LogStruct> logLevelMap {{
			{ERROR, {1, "Error", "\033[0m\033[0;101m\033[1;90m", true}},
			{WARNING, {100, "Warning", "\033[0m\033[40m\033[0;33m", false}},
			{INFORMATION, {200, "Information", "\033[0m\033[40m\033[0;37m", false}},
			{VERBOSE, {300, "Verbose", "\033[0m\033[40m\033[0;35m", false}},
			{DEBUG, {400, "Debug", "\033[0m\033[40m\033[0;32m", false}},
			{TRACE, {500, "Trace", "\033[0m\033[40m\033[0;36m", false}}
		}};

		const std::map<ProjectHSI_Bot_Shared_CLogger_LogLevel,LogStruct> moduleLogLevelMap {{
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::ERROR, {1, "Error", "\033[0m\033[0;101m\033[1;90m", true}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::WARNING, {100, "Warning", "\033[0m\033[40m\033[0;33m", false}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::INFORMATION, {200, "Information", "\033[0m\033[40m\033[0;37m", false}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::VERBOSE, {300, "Verbose", "\033[0m\033[40m\033[0;35m", false}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::DEBUG, {400, "Debug", "\033[0m\033[40m\033[0;32m", false}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::TRACE, {500, "Trace", "\033[0m\033[40m\033[0;36m", false}}
		}};

		/*!
		\brief Gets a concise string from a sourceLocation.

		\note Do not use std::source_location::current() here. Instead, pass the source location into the call site, and use *that* for the argument.
		*/
		inline std::string getSourceLocationString(const std::source_location logSource) {
			return std::format("{}::{}:{}", logSource.file_name(), logSource.function_name(), logSource.line());
		}

		/*!
		\brief The other inline functions map to this and let you use this function more conveniently.
		*/
		void log(const LogStruct &logStruct, std::string logMessage, std::string logSource);

		/*!
		\see ::ProjectHSI_Bot::CLogger::log(const LogStruct &logStruct, std::string logMessage, std::string logSource)
		*/
		inline void log(const ProjectHSI_Bot_Shared_CLogger_LogLevel logLevel, const char *logMessage, std::string logSource) {
			log(moduleLogLevelMap.at(logLevel), std::string(logMessage), logSource);
		}
		/*!
		\see ::ProjectHSI_Bot::CLogger::log(const LogStruct &logStruct, std::string logMessage, std::string logSource)
		*/
		inline void log(const ProjectHSI_Bot_Shared_CLogger_LogStruct &logStruct, const char *logMessage, std::string logSource) {
			log(LogStruct(logStruct), std::string(logMessage), logSource);
		}

		/*!
		\see ::ProjectHSI_Bot::CLogger::log(const LogStruct &logStruct, std::string logMessage, std::string logSource)
		*/
		inline void log(const LogLevel logLevel, std::string logMessage, const std::source_location logSource = std::source_location::current()) {
			return log(logLevelMap.at(logLevel), logMessage, getSourceLocationString(logSource));
		}
		/*!
		\see ::ProjectHSI_Bot::CLogger::log(const LogStruct &logStruct, std::string logMessage, std::string logSource)
		*/
		inline void log(const LogLevel logLevel, std::string logMessage, std::string logSource) {
			return log(logLevelMap.at(logLevel), logMessage, logSource);
		}
		/*!
		\see ::ProjectHSI_Bot::CLogger::log(const LogStruct &logStruct, std::string logMessage, std::string logSource)
		*/
		inline void log(const LogStruct &logStruct, std::string logMessage, const std::source_location logSource = std::source_location::current()) {
			return log(logStruct, logMessage, getSourceLocationString(logSource));
		}
	}
}