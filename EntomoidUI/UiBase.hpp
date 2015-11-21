#pragma once
#include <sstream>
#include <iostream>
#include <string>

#ifdef _MSC_VER
#include "WinUi.hpp"
#endif

namespace entomoid {

	class WindowBasic {
	public:
		WindowBasic() {}
	};

	template <typename... Mixins>
	class Window : public WindowBase, public Mixins... {
	public:
		Window() : Mixins()...
		{}

		void derp() { std::cout << "Derp" << std::endl; }
	};
}