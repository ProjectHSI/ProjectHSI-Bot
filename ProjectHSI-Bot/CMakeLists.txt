# CMakeList.txt : CMake project for ProjectHSI-Bot, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable(ProjectHSI-Bot "ProjectHSI-Bot.cpp"  "Module/SharedLibraryManagement.cpp" "Module/Interface/SharedLibraryManagement.cpp" "ApplicationContext.cpp" "Module/ABICheck.cpp" "Module/BasicABIFunctions.cpp")

set_property(TARGET ProjectHSI-Bot PROPERTY CXX_STANDARD 20)

target_link_libraries(ProjectHSI-Bot PRIVATE ProjectHSI-Bot-Shared)

if(TARGET SDL2::SDL2main)
    target_link_libraries(ProjectHSI-Bot PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(ProjectHSI-Bot PRIVATE SDL2::SDL2)

#target_link_libraries(ProjectHSI-Bot PRIVATE SDL2_net::SDL2_net)