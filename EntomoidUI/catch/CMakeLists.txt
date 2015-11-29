project(catch_config CXX)
include(ExternalProject)

if(ANDROID)
# this is a hacky way of working around
# toolchain file limitations. Unfortunately,
# this also means that we need to have run
# a non-android build first (to get a clone
# of the repo)
set(GIT_EXECUTABLE "C:/Program Files (x86)/Git/bin/git.exe")
endif(ANDROID)
find_package(Git REQUIRED)

if(NOT ANDROID)
ExternalProject_Add(
    catch
    PREFIX ${CMAKE_BINARY_DIR}/catch
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)
else()
ExternalProject_Add(
    catch
    PREFIX ${CMAKE_BINARY_DIR}/catch
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

endif()

ExternalProject_Get_Property(catch source_dir)

set(CATCH_INCLUDE ${source_dir}/include CACHE INTERNAL "Folder Path")