#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdint.h>
#include <array>
#include <vector>
#include <memory>

#ifdef _MSC_VER
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
	}
}
