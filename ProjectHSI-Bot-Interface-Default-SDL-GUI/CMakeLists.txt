# CMakeList.txt : CMake project for ProjectHSI-Bot, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library(ProjectHSI-Bot-Interface-Default-SDL-GUI MODULE "ProjectHSI-Bot-Interface-Default-SDL-GUI.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProjectHSI-Bot-Interface-Default-SDL-GUI PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(ProjectHSI-Bot-Interface-Default-SDL-GUI PRIVATE ProjectHSI-Bot-Shared)

target_link_libraries(ProjectHSI-Bot-Interface-Default-SDL-GUI PRIVATE SDL2::SDL2)
#target_link_libraries(ProjectHSI-Bot-Interface-Default-SDL-GUI PRIVATE SDL2_image::SDL2_image)
#target_link_libraries(ProjectHSI-Bot-Interface-Default-SDL-GUI PRIVATE SDL2_mixer::SDL2_mixer)
#target_link_libraries(ProjectHSI-Bot-Interface-Default-SDL-GUI PRIVATE SDL2_ttf::SDL2_ttf)

#target_link_libraries(ProjectHSI-Bot PRIVATE SDL2_net::SDL2_net)