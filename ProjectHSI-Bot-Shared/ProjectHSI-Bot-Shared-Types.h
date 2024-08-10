/*!
\file ProjectHSI-Bot-Shared/ProjectHSI-Bot-Shared-Types.h

\brief A C header file which contains the definitions for types which are expected to be used in a module and in the orchstrator.
*/

#pragma once
#include <stdint.h>
#include <stdio.h>

/*!
\brief The major version of the ABI, in Semantic Version form.

\see ProjectHSI_Bot_Shared_ABIVersion::major
*/
#define ABI_VERSION_MAJOR 0
/*!
\brief The minor version of the ABI, in Semantic Version form.

\see ProjectHSI_Bot_Shared_ABIVersion::minor
*/
#define ABI_VERSION_MINOR 0
/*!
\brief The patch version of the ABI, in Semantic Version form.

\see ProjectHSI_Bot_Shared_ABIVersion::patch
*/
#define ABI_VERSION_PATCH 1

/*!
\brief Used by the orchestrator to communicate it's ABI version to engine/interface.
 
This struct uses the semantic versioning scheme, although it is not entirely compatible with it.
Most notably, it does not have support for release canidate, build metadata, and some more. Only basic version information is supported in this struct.
 
The struct uses the `major.minor.patch`.
*/
struct ProjectHSI_Bot_Shared_ABIVersion {
	/*!
	\brief The major version of the ABI, in Semantic Version form.

	\see #ABI_VERSION_MAJOR
	*/
	unsigned int major {};

	/*!
	\brief The minor version of the ABI, in Semantic Version form.

	\see #ABI_VERSION_MINOR
	*/
	unsigned int minor {};

	/*!
	\brief The patch version of the ABI, in Semantic Version form.

	\see #ABI_VERSION_PATCH
	*/
	unsigned int patch {};
};

struct ProjectHSI_Bot_Shared_SemanticVersion {
	/*!
	\brief The major version of whatever this struct represents.
	*/
	unsigned int major {};

	/*!
	\brief The minor version of whatever this struct represents.
	*/
	unsigned int minor {};

	/*!
	\brief The patch version of whatever this struct represents.
	*/
	unsigned int patch {};

	/*!
	\brief The pre-release identifier of whatever this struct represents.
	*/
	const char *preRelease {};

	/*!
	\brief The build identifier of whatever this struct represents.
	*/
	const char *buildId {};
};

enum ProjectHSI_Bot_Shared_ModuleInformation_Capabilities {
	ProjectHSI_Bot_Shared_ModuleInformation_Capabilities_Engine = 0b001,
	ProjectHSI_Bot_Shared_ModuleInformation_Capabilities_Interface = 0b010,
	ProjectHSI_Bot_Shared_ModuleInformation_Capabilities_Board = 0b100
};

/*!
\brief Used by the module to sent information about it to the orchestrator.

This struct contains several bits of information about the module, like it's name, capabilities, version, and more.
*/
struct ProjectHSI_Bot_Shared_ModuleInformation {
	/*!
	\brief A C string containing the module's public-facing name (not internal, see #id).
	*/
	const char *name;

	/*!
	\brief An integer containing the capabilities of the module.

	The list of capabilities for a given module is defined in ProjectHSI_Bot_Shared_ModuleInformation_Capabilities.

	\see ProjectHSI_Bot_Shared_ModuleInformation_Capabilities
	*/
	uint_least8_t capabilities;

	/*!
	\brief A C string containing the module's identifier.

	\warning Changing this could be dangerous. See Module ID Warning.md
	*/
	const char *id;

	/*!
	\brief A C string containing the author name.
	
	\warning Changing this could be dangerous. See Module ID Warning.md
	*/
	const char *author;

	/*!
	\brief A C string containing the fork's author name.

	This is a **replacement** for the #author field, but for forks. Unless an application will check for this fork ID, changing it will not do anything, meaning this is a safe way to identify a Fork ID.
	*/
	const char *forkAuthor;

	/*!
	\brief A C string containing the fork ID.

	This fork ID can be anything. Applications should check against this if they're trying to find a fork (although, if your fork contains)
	*/
	const char *forkId;
};

/*!
\brief Log level struct used by CLogger, intentionally placed here for modules to use.

You probably won't need this, the log levels in ::ProjectHSI_Bot_Shared_CLogger_LogLevel should do fine.
Internally, the log levels in ::ProjectHSI_Bot_Shared_CLogger_LogLevel map to this struct. See the definitions in ::ProjectHSI_Bot::CLogger::moduleLogLevelMap.
*/
struct ProjectHSI_Bot_Shared_CLogger_LogStruct {
	/*!
	\brief Visibility setting of the log level. Used to determine whether thee log level should be printed to the console.
	*/
	uint_least16_t logLevel;

	/*!
	\brief The prefix of the log level, which will be in brackets to identify it.
	*/
	const char *logPrefix;

	/*!
	\brief A prefix which is added to the beginning of the entire log.

	This property is expected to be used for ASCII text docorations to make logs identifiable. This is a standard string and no special rules apply.
	*/
	const char *asciiPrefix;

	/*!
	\brief If set to true, will direct the log to stderr instead of stdout.
	*/
	bool stderrRedirect;
};

/*!
\brief Log levels used by CLogger, intentionally placed here for modules to use.
*/
enum ProjectHSI_Bot_Shared_CLogger_LogLevel {
	ERROR,
	WARNING,
	INFORMATION,
	VERBOSE,
	DEBUG,
	TRACE
};

/*!
\brief Used by the module to achieve bi-directional communication with the orchestrator.
*/
struct ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers {
	const ProjectHSI_Bot_Shared_ABIVersion (*getOrchestratorAbiVersion)();
	const ProjectHSI_Bot_Shared_SemanticVersion (*getOrchestratorSemanticVersion)();

	/*!
	\brief The standard variant of the log function.

	The first parameter is the message. The second one is the log level.
	\see ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers::logStruct
	*/
	const void (*log)(const char *, ProjectHSI_Bot_Shared_CLogger_LogLevel);
	/*!
	\brief The standard variant of the log function.

	The first parameter is the message. The second one is the log struct.
	\see ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers::log
	*/
	const void (*logStruct)(const char *, ProjectHSI_Bot_Shared_CLogger_LogStruct);

	const char **(*listModules)();
	const ProjectHSI_Bot_Shared_ModuleInformation (*getModule)();

	/*!
	\brief Sends an event into the event queue.
	
	\warning This function may block as it accessing a [mutex-locked variable](https://en.cppreference.com/w/cpp/thread/mutex). Consider this before using the function.

	\note There is no guarantee about what "tick" the orchestrator will read the event on. Lock if needed
	*/
	const void (*sendEvent)(ProjectHSI_Bot_Shared_Event);

	/*!
	\brief Sends an event into the event queue. Unlike sendEvent, this function does not block and instead spins a thread to send the event.

	\note There is no guarantee about what "tick" the orchestrator will read the event on. Lock if needed.
	*/
	const void (*sendEventAsync)(ProjectHSI_Bot_Shared_Event);

	/*!
	\brief Locks the event buffer.

	Use this to write multiple event objects that need to be read at their intended timings.

	\warning This locks the event buffer from reading **and writing** by anything other than the module that locked the event buffer.

	\warning Do not set the timeout argument to an excessive value. Since there is no exception handling, the timeout value is used to force an unlock of the buffer in case the thread that locked the buffer has crashed.
	*/
	const void (*lockEventBuffer)(uint_least16_t);
};

enum ProjectHSI_Bot_Shared_Event_Type {

};

/*!
\brief Used for sending events to the orchestrator.

An event union may only have one event at a time. If you wish to send more events, at once or scheduled, simply send more events. Lock the buffer if needed.
*/
union ProjectHSI_Bot_Shared_Event {
	ProjectHSI_Bot_Shared_Event_Type eventType;
};

/*!
\brief A wrapper for a board.
*/
struct ProjectHSI_Bot_Shared_Bot {

};