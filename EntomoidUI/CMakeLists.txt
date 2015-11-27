cmake_minimum_required(VERSION 3.0)
project(entomoidUI)


add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(catch)
include_directories(${CATCH_INCLUDE} ${COMMON_INCLUDES})
enable_testing(true)
add_subdirectory(test)



