cmake_minimum_required(VERSION 3.22)
file(GLOB_RECURSE example_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

foreach(example_file ${example_files})
     # Create a human readable name.
     get_filename_component(example_filename ${example_file} NAME)
     string(REPLACE ".cpp" "" expample_name ${example_filename})
 
     # Add the test target separately and as part of "make check-tests".
     add_executable(${expample_name} EXCLUDE_FROM_ALL ${example_files})
     target_link_libraries(${expample_name}  pthread  lee_ws)
 
    #  # Set test target properties and dependencies.
    #  set_target_properties(${expample_name}
    #          PROPERTIES
    #          RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
    #          COMMAND ${lee_ws_test_name}
    #          )    
endforeach()






