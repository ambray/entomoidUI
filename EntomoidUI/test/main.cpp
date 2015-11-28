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

#ifdef _WIN32
#define DECORATION	__stdcall

#else
#define DECORATION 
#endif
#define CALLBACK_FUNC(x) reinterpret_cast<int (DECORATION *)(int,int,int,int)>(x)

TEST_CASE("Tests for the utility callback wrapper", "[CallbackWrapper]")
{
	class TestClass {
	private:
		std::shared_ptr<void> cb_;
		int internalCallback(int a, int b, int c, int d)
		{
			return a + b + (c + d);
		}
	public:
		TestClass() { cb_ = utils::closureFromMemberFunction(this, &TestClass::internalCallback); }
		std::shared_ptr<void> getCallback() { return cb_; }
	};

	TestClass tc;
	auto cb_holder = tc.getCallback();

	SECTION("Basic callback-wrapping functionality")
	{
		REQUIRE(cb_holder);
		auto callback = CALLBACK_FUNC(cb_holder.get());
		auto testVal = callback(10, 10, 10, 10); 
		REQUIRE(40 == testVal);
	}
}