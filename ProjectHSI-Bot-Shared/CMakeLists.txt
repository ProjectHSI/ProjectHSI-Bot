# CMakeList.txt : CMake project for ProjectHSI-Bot, include source and define
# project specific logic here.
#

find_package(Doxygen
             OPTIONAL_COMPONENTS dot mscgen dia)

if(NOT ProjectHSIBot_NO_BUILD_TARGETS)
    add_library(ProjectHSI-Bot-Shared INTERFACE)
    target_include_directories(ProjectHSI-Bot-Shared INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

    set_property(TARGET ProjectHSI-Bot-Shared PROPERTY CXX_STANDARD 20)
endif()

doxygen_add_docs(ProjectHSI-Bot-Shared-Docs ${CMAKE_CURRENT_SOURCE_DIR} CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)