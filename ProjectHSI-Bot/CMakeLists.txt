# CMakeList.txt : CMake project for ProjectHSI-Bot, include source and define
# project specific logic here.
#

block()
    try_compile(ProjectHSI_BOT_CXX_COMPILER_COMPLETE SOURCE_FROM_FILE "CXXCompilerCheck.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/CXXCompilerCheck.cpp" CXX_STANDARD 23 CXX_STANDARD_REQUIRED YES)

    message(STATUS ${ProjectHSI_BOT_CXX_COMPILER_COMPLETE})
    if(NOT ${ProjectHSI_BOT_CXX_COMPILER_COMPLETE})
        message(FATAL_ERROR "Your compiler doesn't the needed features required for ProjectHSI-Bot to compile, or it doesn't have them in the right place. ProjectHSI-Bot will not compile.")
    endif()
endblock()

# Add source to this project's executable.
add_executable(ProjectHSI-Bot "ProjectHSI-Bot.cpp" "Module/SharedLibraryManagement.cpp" "ApplicationContext.cpp" "Module/ABICheck.cpp" "Module/BasicABIFunctions.cpp"  "EventLoop.cpp")

set_property(TARGET ProjectHSI-Bot PROPERTY CXX_STANDARD 23)

target_link_libraries(ProjectHSI-Bot PRIVATE ProjectHSI-Bot-Shared)

target_link_libraries(ProjectHSI-Bot
    PRIVATE
#    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_include_directories(ProjectHSI-Bot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(ProjectHSI-Bot PRIVATE SDL2_net::SDL2_net)