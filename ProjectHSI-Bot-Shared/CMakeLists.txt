# CMakeList.txt : CMake project for ProjectHSI-Bot, include source and define
# project specific logic here.
#

if(NOT ProjectHSIBot_NO_BUILD_TARGETS)
    add_library(ProjectHSI-Bot-Shared INTERFACE)
    target_include_directories(ProjectHSI-Bot-Shared INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

    set_property(TARGET ProjectHSI-Bot-Shared PROPERTY CXX_STANDARD 20)
endif()