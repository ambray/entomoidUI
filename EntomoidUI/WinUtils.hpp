#pragma once
#include <Windows.h>
#include <sstream>
#include <vector>
#include <array>
#include <stdint.h>
#include <memory>
#include "Utils.hpp"

#define WRAP_WINDOWS_RUNTIME_ERROR(msg)\
	do {\
		std::stringstream ss;\
		ss << msg << " Error: " << GetLastError();\
		throw std::runtime_error(ss.str());\
	} while(0)

namespace entomoid {
	namespace utils {

		std::shared_ptr<void> windows_getCallback(size_t thisptr, void* fptr);

		template <typename T, typename F>
		std::shared_ptr<void> inline platformGetCallback(T thisptr, F fptr)
		{
			return windows_getCallback((size_t)thisptr, (void*&)fptr);
		}
	
	}
}
