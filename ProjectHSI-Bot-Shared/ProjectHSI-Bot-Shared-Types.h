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

This struct contains several bits of information about the module, like it's internal name, capabilities, version, and more.
*/
struct ProjectHSI_Bot_Shared_ModuleInformation {
	/*!
	\brief A C string containing the module's internal identifier.
	*/
	const char *name;

	/*!
	\brief An integer containing the capabilities of the module.

	The list of capabilities for a given module is defined in ProjectHSI_Bot_Shared_ModuleInformation_Capabilities.

	\see ProjectHSI_Bot_Shared_ModuleInformation_Capabilities
	*/
	uint_least8_t capabilities;
};

/*!
\brief Used by the module to achieve bi-directional communication with the orchestrator.
*/
struct ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers {
	const ProjectHSI_Bot_Shared_ABIVersion (*getOrchestratorAbiVersion)();
	const ProjectHSI_Bot_Shared_SemanticVersion (*getOrchestratorSemanticVersion)();

	const char **(*listModules)();
	const ProjectHSI_Bot_Shared_ModuleInformation (*getModule)();
};