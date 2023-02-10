cmake_minimum_required(VERSION 3.23)
project(LeeWS LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)



##########################################
# "make check-lint"
##########################################

file(GLOB_RECURSE LeeWS_LINT_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/example/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/example/*.h"
        )

# Balancing act: cpplint.py takes a non-trivial time to launch,
# so process 12 files per invocation, while still ensuring parallelism
add_custom_target(check-lint echo '${LeeWS_LINT_FILES}' | xargs -n12 -P8
        ${CPPLINT_BIN}
        --verbose=2 --quiet
        --linelength=120
        --filter=-legal/copyright,-build/header_guard,-runtime/references # https://github.com/cpplint/cpplint/issues/148
        )