cmake_minimum_required(VERSION 3.22)

file(GLOB_RECURSE LEE_WS_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*/*test.cpp")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# #########################################
# "make XYZ_test"
# #########################################
foreach (lee_ws_test_source ${LEE_WS_TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(lee_ws_test_filename ${lee_ws_test_source} NAME)
    string(REPLACE ".cpp" "" lee_ws_test_name ${lee_ws_test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${lee_ws_test_name} EXCLUDE_FROM_ALL ${lee_ws_test_source})
    target_link_libraries(${lee_ws_test_name}  pthread ${GTEST_BOTH_LIBRARIES} lee_ws)

    # Set test target properties and dependencies.
    set_target_properties(${lee_ws_test_name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
            COMMAND ${lee_ws_test_name}
            )
endforeach ()