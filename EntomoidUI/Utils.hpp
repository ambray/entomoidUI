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

namespace entomoid {
	namespace utils {
		enum class ClosureType {
			Callback,
		};

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
