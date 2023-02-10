cmake_minimum_required(VERSION 3.23)

include_directories(inc/)

file(GLOB lee_ws_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp)
foreach(file IN LISTS lee_ws_files)
    # message(${file})

endforeach(file)


add_library(lee_ws STATIC ${lee_ws_files})


find_package(Threads REQUIRED)
target_link_libraries(lee_ws Threads::Threads)
# set(LEE_WS_LIBS )
# find_package(Threads REQUIRED)


target_include_directories(
        lee_ws PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
