call "%VS140COMNTOOLS%vsvars32.bat"

if "%1"=="Win32" (
   call cmake.exe -G "Visual Studio 14 2015" CMakeLists.txt
)
if "%1"=="x64" (
   call cmake.exe -G "Visual Studio 14 2015 Win64" CMakeLists.txt
)

cmake.exe --build . --target ALL_BUILD --config Debug
cmake.exe --build . --target ALL_BUILD --config Release