/*!
\file ProjectHSI-Bot/ApplicationContext.hpp

\brief This file supplies the ProjectHSI_Bot::ApplicationContext namespace.

This module provides context about the application environment.

\see ProjectHSI-Bot/ApplicationContext.cpp
*/

#include <filesystem>
#include <string>

namespace ProjectHSI_Bot {
	namespace ApplicationContext {
		/*!
		\brief The base path of the application executable.
		\see ProjectHSI_Bot::ApplicationContext::basePathString
		\see ProjectHSI_Bot::ApplicationContext::basePathPath
		*/
		extern const char *basePathChar;
		/*!
		\brief The pref path of the organization "ProjectHSI" and the application name "ProjectHSI-Bot".

		\warning This may be a nullptr - confirm before using.
		\see ProjectHSI_Bot::ApplicationContext::prefPathString
		\see ProjectHSI_Bot::ApplicationContext::prefPathPath
		*/
		extern const char *prefPathChar;
		/*!
		\brief The base path of the application executable in a std::string.
		\see ProjectHSI_Bot::ApplicationContext::basePathString
		\see ProjectHSI_Bot::ApplicationContext::basePathPath
		*/
		extern std::string basePathString;
		/*!
		\brief The pref path in a std::string.
		\see ProjectHSI_Bot::ApplicationContext::prefPathChar
		\see ProjectHSI_Bot::ApplicationContext::prefPathPath
		*/
		extern std::string prefPathString;
		/*!
		\brief The base path of the application in a std::filesystem::path.
		\see ProjectHSI_Bot::ApplicationContext::basePathChar
		\see ProjectHSI_Bot::ApplicationContext::basePathString
		*/
		extern std::filesystem::path basePathPath;
		/*!
		\brief The pref path in a std::filesystem::path.
		\see ProjectHSI_Bot::ApplicationContext::prefPathChar
		\see ProjectHSI_Bot::ApplicationContext::prefPathString
		*/
		extern std::filesystem::path prefPathPath;

		/*!
		\brief Initalizes the variables in the ApplicationContext namespace.

		\warning You must call this function *before* accessing any of the variables defined in ProjectHSI_Bot::ApplicationContext.
		*/
		void initalize();
		/*!
		\brief Destroys the variables in the ApplicationContext namespace.
		*/
		void destroy();
	}
}