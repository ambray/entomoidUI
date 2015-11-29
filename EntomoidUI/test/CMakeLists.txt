include_directories(${CATCH_INCLUDE} ${COMMON_INCLUDES})
add_executable(entomoidTest main.cpp UtilTests.cpp)
add_dependencies(entomoidTest catch)
target_link_libraries(entomoidTest LINK_PUBLIC entomoid)
