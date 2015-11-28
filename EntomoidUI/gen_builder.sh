#!/bin/bash

cmake CMakeLists.txt
cmake --build . --config Debug
ctest -C Debug