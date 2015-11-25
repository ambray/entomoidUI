add_executable(entomoidDemo main.cpp)

target_link_libraries(entomoidDemo LINK_PUBLIC entomoid)

if(WIN32)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")
endif(WIN32)
