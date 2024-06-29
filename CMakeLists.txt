# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ProjectHSI-Bot")

option(ProjectHSIBot_NO_BUILD_TARGETS "Disables all builds targets, and only includes the ProjectHSI-Bot-Shared documentation target (if ssupport). Note that the documentation can still be generated with this option enabled (assuming your system has Doxygen installed)." FALSE)
option(ProjectHSIBot_SDL_STATIC "Compiles SDL statically. May be good for rapid iteration." NO)

if(NOT ProjectHSIBot_NO_BUILD_TARGETS)

	# Include third-party dependencies as submodules.
	block(SCOPE_FOR VARIABLES)
		set(BUILD_SHARED_LIBS TRUE)
		if(${ProjectHSIBot_SDL_STATIC})
			set(SDL_SHARED NO)
			set(SDL_STATIC YES)
		else()
			set(SDL_SHARED YES)
			set(SDL_STATIC NO)
		endif()

		#add_subdirectory("third_party/opus")

		add_subdirectory("third_party/SDL" EXCLUDE_FROM_ALL)
		#add_subdirectory("third_party/SDL_net" EXCLUDE_FROM_ALL)
		#set(SDL2MIXER_VENDORED ON) # inconsistent behaviour between platforms lol
		#add_subdirectory("third_party/SDL_mixer" EXCLUDE_FROM_ALL)
		#add_subdirectory("third_party/SDL_ttf" EXCLUDE_FROM_ALL)
		#add_subdirectory("third_party/SDL_image" EXCLUDE_FROM_ALL)
	endblock()

endif()

if(NOT ProjectHSIBot_NO_BUILD_TARGETS)
	add_subdirectory("ProjectHSI-Bot-Shared")
	add_subdirectory("ProjectHSI-Bot-Interface-Default-SDL-GUI")
	add_subdirectory("ProjectHSI-Bot")

	#enable_testing()
	#include("ProjectHSI-Bot-Shared-Tests/CMakeLists.txt")
endif()

include("Doxygen.cmake")
