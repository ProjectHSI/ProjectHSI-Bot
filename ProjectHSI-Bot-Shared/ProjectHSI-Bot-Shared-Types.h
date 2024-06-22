/*!
\file ProjectHSI-Bot-Shared/ProjectHSI-Bot-Shared-Types.h

\brief A C header file which contains the definitions for types which are expected to be used in a module and in the orchstrator.
*/

#pragma once

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
	unsigned int major;

	/*!
    \brief The minor version of the ABI, in Semantic Version form.
	
	\see #ABI_VERSION_MINOR
    */
	unsigned int minor;

	/*!
    \brief The patch version of the ABI, in Semantic Version form.

	\see #ABI_VERSION_PATCH
    */
	unsigned int patch;
};