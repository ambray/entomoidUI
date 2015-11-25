
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB entomoid_SOURCES *.cpp)
file(GLOB entomoid_HEADERS *.hpp)
add_library(entomoid ${entomoid_SOURCES} ${entomoid_HEADERS})
target_include_directories(entomoid PUBLIC ${entomoid_SOURCE_DIR})




if(UNIX)
# TODO: populate build options | (APPLE/android?)
else(UNIX)
if(WIN32)
add_library(rpcrt4 STATIC IMPORTED)
set_target_properties(rpcrt4 PROPERTIES IMPORTED_LOCATION "rpcrt4.lib")
target_link_libraries(entomoid rpcrt4)
endif(WIN32)
endif(UNIX)




