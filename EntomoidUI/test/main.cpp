#include <string>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <memory>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "..\src\UiBase.hpp"
#include "..\src\Utils.hpp"
#include "..\src\WinUtils.hpp"

using namespace entomoid;



void test_func()
{
    CHECK(1 == 1);
}