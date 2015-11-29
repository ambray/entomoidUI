
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB entomoid_SOURCES *.cpp)
file(GLOB entomoid_HEADERS *.hpp)
if(WIN32)
    file(GLOB platform_SOURCES win/*.cpp)
    file(GLOB platform_HEADERS win/*.hpp)
endif(WIN32)
if(UNIX)
    file(GLOB platform_SOURCES nix/*.cpp)
    file(GLOB platform_HEADERS nix/*.hpp)
endif(UNIX)
if(ANDROID)
    file(GLOB platform_SOURCES android/*.cpp)
    file(GLOB platform_HEADERS android/*.hpp)
endif(ANDROID)

add_library(entomoid ${entomoid_SOURCES} ${entomoid_HEADERS} ${platform_SOURCES} ${platform_HEADERS})
target_include_directories(entomoid PUBLIC ${entomoid_SOURCE_DIR})


if(UNIX)
if(ANDROID)

else(ANDROID)
    set_target_properties(entomoid PROPERTIES LINKER_LANGUAGE CXX)
    find_package(PkgConfig)
    pkg_check_modules(xcb_pkg xcb)
    find_library(xcb_libs NAMES xcb libxcb PATHS ${xcb_pkg_LIBRARY_DIRS})
    target_link_libraries(entomoid ${xcb_libs})
endif(ANDROID)
endif(UNIX)
if(WIN32)
    add_library(rpcrt4 STATIC IMPORTED)
    set_target_properties(rpcrt4 PROPERTIES IMPORTED_LOCATION "rpcrt4.lib")
    target_link_libraries(entomoid rpcrt4)
endif(WIN32)





