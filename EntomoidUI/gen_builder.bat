call "%VS140COMNTOOLS%vsvars32.bat"

if "%1"=="Win32" (
   call cmake.exe -G "Visual Studio 14 2015" CMakeLists.txt
)
if "%1"=="x64" (
   call cmake.exe -G "Visual Studio 14 2015 Win64" CMakeLists.txt
)
if "%1"=="android" (
    call cmake.exe -DCMAKE_TOOLCHAIN_FILE="..\android.toolchain.cmake" -DANDROID_NDK=%HOMEPATH%\android-ndk-r10e -DANDROID_ABI="x86" -DCMAKE_BUILD_TYPE=Debug -GNinja
    call cmake.exe --build .
    goto END
)


if "%2"=="--nobuild" (
    goto END
)
cmake.exe --build . --target ALL_BUILD --config Debug
cmake.exe --build . --target ALL_BUILD --config Release
ctest.exe -C Debug
ctest.exe -C Release

:END