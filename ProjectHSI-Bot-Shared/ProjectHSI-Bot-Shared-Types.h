#pragma once

/**
 * @brief Used by the orchestrator to communicate it's ABI version to engine/interface.
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