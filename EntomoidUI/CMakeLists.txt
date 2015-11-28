cmake_minimum_required(VERSION 3.0)
project(entomoidUI)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(catch)
include_directories(${CATCH_INCLUDE} ${COMMON_INCLUDES})
add_subdirectory(test)

enable_testing()
macro(create_test target)
    add_test(NAME ${target} COMMAND ${target})
endmacro(create_test)

create_test(entomoidTest)


