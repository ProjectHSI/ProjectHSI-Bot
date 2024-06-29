project("ProjectHSI-Bot-Shared-Tests-CCompatibility" LANGUAGES C)

add_executable(ProjectHSI-Bot-Shared-Tests-CCompatibility "CCompatibility.c")
target_link_libraries(ProjectHSI-Bot-Shared-Tests-CCompatibility PRIVATE ProjectHSI-Bot-Shared)