#include <string>
#include <iostream>
#include <sstream>
#ifdef _WIN32
#define DECORATION	__stdcall
#include "../src/win/WinUtils.hpp"
#include <windows.h>
#else
#define DECORATION 
#endif
#include <memory>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../src/UiBase.hpp"
#include "../src/Utils.hpp"


using namespace entomoid;



#define CALLBACK_FUNC(x) reinterpret_cast<int (DECORATION *)(int,int,int,int)>(x)

TEST_CASE("Tests for the utility callback wrapper", "[CallbackWrapper]")
{
	class TestClass {
	private:
		int internal_;
		std::shared_ptr<void> cb_;
		int internalCallback(int a, int b, int c, int d)
		{
			// General functionality test
			if(10 == a && 10 == b && 10 == c && 10 == d)
				return a + b + (c + d);

			// Individual parameter validation tests
			if(11 == a)
				return a;

			if(12 == b)
				return b;

			if(13 == c)
				return c;

			if(14 == d)
				return d;

			// can access private class members? (e.g., proper use of this ptr)
			if(300 == a)
				return internal_;

			return 0;
		}
	public:
		TestClass() : internal_(100) { cb_ = utils::closureFromMemberFunction(this, &TestClass::internalCallback); }
		std::shared_ptr<void> getCallback() { return cb_; }
	};

	TestClass tc;
	auto cb_holder = tc.getCallback();
	REQUIRE(cb_holder);
	auto callback = CALLBACK_FUNC(cb_holder.get());

	SECTION("Basic callback-wrapping functionality")
	{	
		auto testVal = callback(10, 10, 10, 10); 
		REQUIRE(40 == testVal);
	}

	SECTION("Parameter location validation")
	{
		auto res = callback(11, 0, 0, 0);
		REQUIRE(11 == res);

		res = callback(0, 12, 0, 0);
		REQUIRE(12 == res);

		res = callback(0, 0, 13, 0);
		REQUIRE(13 == res);

		res = callback(0, 0, 0, 14);
		REQUIRE(14 == res);
	}

	SECTION("Use this pointer with callback")
	{
		auto res = callback(300, 0, 0, 0);
		REQUIRE(100 == res);
	}
}