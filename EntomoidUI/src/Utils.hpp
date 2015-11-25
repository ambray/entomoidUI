#pragma once
/********************************************************************************
* The MIT License (MIT)
*
* Copyright (c) 2015, Aaron M. Bray, aaron.m.bray@gmail.com

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*********************************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdint.h>
#include <array>
#include <vector>
#include <memory>
#include "Settings.hpp"

#ifdef _WIN32 
#include "WinUtils.hpp"
#endif

/**
* Some helper macros to provide compile time interface validation	
* (e.g., it allows easy checking to ensure that the decorated function "fname" 
* matching signature "def" actually exists in class cls).
* They are intended to be used as a pair; ENTOMOID_DECLARE_HAS_FUNC adds the forward
* template declaration, and ENTOMOID_CHECK_HAS_FUNC attempts to instantiate it and
* retrieve the value. If a function matching the signature is not found in the
* provided class, compilation errors will result.
* Ex:
*	class TestClass {
*	public:
*		void test() {}
*	};
*   ...
*   ENTOMOID_DECLARE_HAS_FUNC(TestClass, test, void());
*	...
*	std::cout << "Does TestClass have func 'void test()'? " 
*			  << ENTOMOID_CHECK_HAS_FUNC(TestClass, test, void()) << std::endl;
*
* Output: 
*		"Does TestClass have func 'void test()'? 1" (or compilation error, if test() doesn't exist).
*/
/// Example use: ENTOMOID_DECLARE_HAS_FUNC(TestClass, test, void());
#define ENTOMOID_DECLARE_HAS_FUNC(cls, fname, def)\
	template<typename, typename T>\
	struct entomoid_ensure_has_##fname {\
		static_assert(std::integral_constant<T, false>::value, "Failed to find function " #fname " during template instantiation!");\
	};\
	template <typename C, typename R, typename... Args>\
	struct entomoid_ensure_has_##fname<C, R(Args...)> {\
	private:\
		template <typename T>\
		static constexpr auto validate(T*)\
			-> typename std::is_same<decltype(std::declval<T>().##fname(std::declval<Args>()...)), R>::type;\
		template <typename>\
		static constexpr std::false_type validate(...);\
		using type = decltype(validate<C>(0));\
	public:\
		static constexpr bool value = type::value;\
	} 

/// Example of use (same as above): ENTOMOID_CHECK_HAS_FUNC(TestClass, test, void());
#define ENTOMOID_CHECK_HAS_FUNC(cls, fname, def)\
	entomoid_ensure_has_##fname<cls, def>::value

namespace entomoid {
	namespace utils {


		enum class ClosureType {
			Callback,
		};


		template <typename T, typename S>
		T union_cast(S s)
		{
			static_assert(sizeof(T) == sizeof(S), "Size mismatch detected in union cast!");
			union { S s; T t; } u;
			u.s = s;
			return u.t;
		}

		template <typename T, typename F>
		std::shared_ptr<void> inline makeClosure(T thisptr, F cb, ClosureType type=ClosureType::Callback)
		{
			return platformGetCallback(thisptr, cb);
		}

		template <typename T>
		void printBytes(T start, T end)
		{
			std::stringstream ss;
			ss << std::hex << std::setfill('0');
			for (; start != end; ++start) {
				ss << " 0x" << std::setw(2) << static_cast<unsigned int>(*start);
			}

			std::cout << ss.str() << std::endl;
		}

		template <typename T>
		EventType inline translateEvent(T t)
		{
			return platformTranslateEvent(t);
		}
		
	}
}
