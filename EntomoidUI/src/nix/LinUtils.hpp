#pragma once

#include <memory>
#include "../Utils.hpp"

namespace entomoid {
    namespace utils {
        template <typename T, typename F>
        std::shared_ptr<void> inline platformGetCallback(T thisptr, F fptr)
        {
            return std::shared_ptr<void>();
        };

        template <typename T>
        EventType inline platformTranslateEvent(T t)
        {
            return EventType::EventOther;
        }
    }
}
