#pragma once

#define ABI_VERSION_X 0
#define ABI_VERSION_Y 0
#define ABI_VERSION_Z 1

/**
 * @brief Used by the orchestrator to communicate it's ABI version to engine/interface.
 * 
 * This struct uses the semantic versioning scheme, although it is not entirely compatible with it.
 * Most notably, it does not have support for release canidate, build metadata, and some more. Only basic version information is supported in this struct.
 * 
 * The struct uses the `major.minor.patch`.
 */
struct ProjectHSI_Bot_Shared_ABIVersion {
	/**
     * @brief The major version of the ABI, in Semantic Version form.
     */
	unsigned int major;

	/**
     * @brief The minor version of the ABI, in Semantic Version form.
     */
	unsigned int minor;

	/**
     * @brief The patch version of the ABI, in Semantic Version form.
     */
	unsigned int patch;
};