find_package(Doxygen
             OPTIONAL_COMPONENTS dot mscgen dia)

if(DOXYGEN_FOUND)
    include("DoxygenConfig.cmake")
    doxygen_add_docs(ProjectHSI-Bot-Shared-Docs ProjectHSI-Bot ProjectHSI-Bot-Shared CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
elseif(ProjectHSIBot_NO_BUILD_TARGETS) # Doxygen cannot be installed if this condition is reached.
    message(WARNING "Doxygen is not installed, yet NO_BUILD_TARGETS is enabled. This is probably not what you want, since the documentation target will not be generated. Please install Doxygen to generate the documentation target.")
endif()