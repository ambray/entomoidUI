cmake_minimum_required(VERSION 3.0)
project(entomoidUI)

include_directories(${entomoidUI_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB entomoid_SOURCES *.cpp)
file(GLOB entomoid_HEADERS *.hpp)

if(WIN32)
add_library(rpcrt4 STATIC IMPORTED)
set_target_properties(rpcrt4 PROPERTIES IMPORTED_LOCATION "rpcrt4.lib")
endif(WIN32)

add_executable(entomoidUI ${entomoid_SOURCES} ${entomoid_HEADERS})

if(WIN32)
target_link_libraries(entomoidUI rpcrt4)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")
endif(WIN32)

install(TARGETS entomoidUI DESTINATION bin)