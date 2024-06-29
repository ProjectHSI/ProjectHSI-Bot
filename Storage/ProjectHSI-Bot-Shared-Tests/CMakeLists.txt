file(GLOB ProjectHSI_Bot_Shared_Tests_Tests LIST_DIRECTORIES TRUE "${CMAKE_SOURCE_DIR}/ProjectHSI-Bot-Shared-Tests/Tests/*")

foreach(ProjectHSI_Bot_Shared_Tests_Test IN LISTS ProjectHSI_Bot_Shared_Tests_Tests)
    get_filename_component(ProjectHSI_Bot_Shared_Tests_Test_Name ${ProjectHSI_Bot_Shared_Tests_Test} NAME)

    add_test(${ProjectHSI_Bot_Shared_Tests_Test_Name} ${CMAKE_CTEST_COMMAND}
       --build-and-test "${CMAKE_SOURCE_DIR}/ProjectHSI-Bot-Shared-Tests/Tests/${ProjectHSI_Bot_Shared_Tests_Test_Name}"
                        "${CMAKE_BINARY_DIR}/ProjectHSI-Bot-Shared-Tests/Tests/${ProjectHSI_Bot_Shared_Tests_Test_Name}"
       --build-generator ${CMAKE_GENERATOR}
       --build-makeprogram ${CMAKE_MAKE_PROGRAM}
       --build-project ${ProjectHSI_Bot_Shared_Tests_Test_Name})
endforeach()