/*!
\file ProjectHSI-Bot/Logger.hpp

\brief Defines various logging functions.

This file supplies the `ProjectHSI_Bot::CLogger` namespace and implements the informal CLogger standard.

\see ProjectHSI-Bot/Logger.cpp
*/

#pragma once

#include <version>

#include <cstdint>
#ifdef __cpp_lib_format
#include <format>
#endif
#include <map>
#include <ProjectHSI-Bot-Shared-Types.h>
#ifdef __cpp_lib_source_location
#include <source_location>
#endif

#pragma warning __cpp_lib_source_location

#include <string>
#include <string_view>
#include <regex>
#include <chrono>
//#include "Logger.cpp"

namespace ProjectHSI_Bot {
	namespace CLogger {
		/*!
		\brief Log level struct used by CLogger, for easier use interally.

		You probably won't need this, the log levels in ::ProjectHSI_Bot::CLogger::LogLevel should do fine.
		Internally, the log levels in ::ProjectHSI_Bot::CLogger::LogLevel map to this struct. See the definitions in ProjectHSI-Bot/Logger.hpp.
		*/
		struct LogStruct {
			/*!
			\brief Visibility setting of the log level. Used to determine whether the log level should be printed to the console.

			This also controls whether the log is directed to stderr. This value should be negative for a redirection.
			*/
			long long logLevel;

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
			\brief Constructs a ::ProjectHSI_Bot::CLogger::LogStruct.
			*/
			LogStruct(const long long& logLevel, const std::string& logPrefix, const std::string& asciiPrefix) {
				this->logLevel = logLevel;
				this->logPrefix = logPrefix;
				this->asciiPrefix = asciiPrefix;
			}

			// NOTE: Removed since probably not needed.
			/*!
			\brief Constructs a ::ProjectHSI_Bot::CLogger::LogStruct, but with the logLevel being a standard int rather than a unsigned long long.
			*/
			/*
			LogStruct(int logLevel, const std::string logPrefix, std::string asciiPrefix) {
				this->logLevel = static_cast< unsigned long long >(logLevel);
				this->logPrefix = logPrefix;
				this->asciiPrefix = asciiPrefix;
			}
			*/

			/*!
			\brief Constructs a ::ProjectHSI_Bot::CLogger::LogStruct from a ::ProjectHSI_Bot_Shared_CLogger_LogStruct.
			*/
			LogStruct(const ProjectHSI_Bot_Shared_CLogger_LogStruct& moduleLogStruct) {
				this->logLevel = moduleLogStruct.logLevel;
				this->logPrefix = std::string(moduleLogStruct.logPrefix);
				this->asciiPrefix = std::string(moduleLogStruct.asciiPrefix);
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

		/*!
		\brief Maps a ::ProjectHSI_Bot::CLogger::LogLevel to a ::ProjectHSI_Bot::CLogger::LogStruct.
		*/
		const std::map<LogLevel, LogStruct> logLevelMap {{
			{ERROR, {-1, "Error", "\033[0m\033[0;101m\033[1;90m"}},
			{WARNING, {100, "Warning", "\033[0m\033[40m\033[0;33m"}},
			{INFORMATION, {200, "Information", "\033[0m\033[40m\033[0;37m"}},
			{VERBOSE, {300, "Verbose", "\033[0m\033[40m\033[0;35m"}},
			{DEBUG, {400, "Debug", "\033[0m\033[40m\033[0;32m"}},
			{TRACE, {500, "Trace", "\033[0m\033[40m\033[0;36m"}}
		}};

		/*!
		\brief Maps a ::ProjectHSI_Bot_Shared_CLogger_LogLevel to a ::ProjectHSI_Bot::CLogger::LogStruct.
		*/
		const std::map<ProjectHSI_Bot_Shared_CLogger_LogLevel, LogStruct> moduleLogLevelMap {{
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::ERROR, {-1, "Error", "\033[0m\033[0;101m\033[1;90m"}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::WARNING, {100, "Warning", "\033[0m\033[40m\033[0;33m"}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::INFORMATION, {200, "Information", "\033[0m\033[40m\033[0;37m"}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::VERBOSE, {300, "Verbose", "\033[0m\033[40m\033[0;35m"}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::DEBUG, {400, "Debug", "\033[0m\033[40m\033[0;32m"}},
			{ProjectHSI_Bot_Shared_CLogger_LogLevel::TRACE, {500, "Trace", "\033[0m\033[40m\033[0;36m"}}
		}};

		/*!
		\brief Gets a concise string from a sourceLocation.

		\note Do not use std::source_location::current() here. Instead, pass the source location into the call site, and use *that* for the argument.
		*/
	#ifdef __cpp_lib_source_location
		inline std::string getSourceLocationString(const std::source_location logSource) {
		#ifdef __cpp_lib_source_location
			return std::format("{}::{}:{}", logSource.file_name(), logSource.function_name(), logSource.line());
		#else
			int nBuffer = snprintf(nullptr, 0, "%s::%s:%s", logSource.file_name(), logSource.function_name(), logSource.line());
			std::string buffer {};
			buffer.resize(static_cast< std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type >(nBuffer) + 1);
			snprintf(buffer.data(), nBuffer, "%s::%s:%s", logSource.file_name(), logSource.function_name(), logSource.line());

			return buffer;
		#endif
		}
	#endif

		/*!
		\brief Logs a CLogger-style message to stdout and stderr.
		
		The other inline functions map to this and let you use this function more conveniently.

		\param[in] logStruct The log struct defining the log level and related properties.
		\param[in] logMessage The log message.
		\param[in] logSource The source of the log message.
		*/
		template<typename... Args>
		void log(const LogStruct &logStruct, const std::string &logMessage, const std::string &logSource, Args... args);

		template<typename... Args>
		void log(const LogStruct &logStruct, const std::string& logMessage, const std::string& logSource, Args... args) {
		// (ascii prefix) [(time)] [(source)] ((level)): (text)\n

		#ifdef __cpp_lib_format
			const std::regex printfReplacementCharacter("\%*");

			const std::string stdFormatCompat = std::regex_replace(logMessage, printfReplacementCharacter, "{}");

			fprintf(
				logStruct.logLevel < 0 ? stderr : stdout,
				"%s[%s] [%s] (%s): %s\n",
				logStruct.asciiPrefix.data(),
				std::format("{0:%c}", std::chrono::system_clock::now()).data(),
				logSource.data(),
				logStruct.logPrefix.data(),
				logMessage.data());

		#else
		//#pragma warning( push )
		//#pragma warning( disable : 4774 )
			int nBuffer = snprintf(nullptr, 0, logMessage.data(), &args...);
			std::string buffer {};
			buffer.resize(static_cast< std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type >(nBuffer) + 1);
			snprintf(buffer.data(), nBuffer, logMessage.data(), &args...);
		//#pragma warning( pop )

			fprintf(
				logStruct.logLevel < 0 ? stderr : stdout,
				"%s(%s): %s\n",
				logStruct.asciiPrefix.data(),
				logStruct.logPrefix.data(),
				buffer.data());
		#endif
		}

		/*!
		\brief Inline helper for ::ProjectHSI_Bot::CLogger::log

		\see ::ProjectHSI_Bot::CLogger::log
		*/
		
		inline void log(const ProjectHSI_Bot_Shared_CLogger_LogLevel logLevel, const char *logMessage, const std::string& logSource) {
			log(moduleLogLevelMap.at(logLevel), std::string(logMessage), logSource);
		}
		/*!
		\brief Inline helper for ::ProjectHSI_Bot::CLogger::log

		\see ::ProjectHSI_Bot::CLogger::log
		*/
		inline void log(const ProjectHSI_Bot_Shared_CLogger_LogStruct &logStruct, const char *logMessage,
			const std::string& logSource
		#ifndef __cpp_lib_source_location
			= ""
		#endif
		) {
			log(LogStruct(logStruct), std::string(logMessage), logSource);
		}

	#ifdef __cpp_lib_source_location
		/*!
		\brief Inline helper for ::ProjectHSI_Bot::CLogger::log

		\see ::ProjectHSI_Bot::CLogger::log
		*/
		template<typename... Args>
		inline void log(const LogLevel logLevel, const std::string& logMessage, const std::source_location& logSource = std::source_location::current(), Args... args) {
			return log(logLevelMap.at(logLevel), logMessage, getSourceLocationString(logSource), &args...);
		}
	#endif
		/*!
		\brief Inline helper for ::ProjectHSI_Bot::CLogger::log

		\see ::ProjectHSI_Bot::CLogger::log
		*/
		template<typename... Args>
		inline void log(const LogLevel logLevel, const std::string& logMessage,
			const std::string& logSource
		#ifndef __cpp_lib_source_location
			= ""
		#endif
			, Args... args) {
			return log(logLevelMap.at(logLevel), logMessage, logSource, &args...);
		}
	#ifdef __cpp_lib_source_location
		/*!
		\brief Inline helper for ::ProjectHSI_Bot::CLogger::log

		\see ::ProjectHSI_Bot::CLogger::log
		*/
		template<typename... Args>
		inline void log(const LogStruct &logStruct, const std::string& logMessage, const std::source_location& logSource = std::source_location::current(), Args... args) {
			return log(logStruct, logMessage, getSourceLocationString(logSource), &args...);
		}
	#endif
	}
}