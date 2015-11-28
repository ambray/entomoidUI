#!/bin/bash

cmake CMakeLists.txt
cmake --build . --config Debug
cmake --build . --config Release
ctest -C Debug
ctest -C Release