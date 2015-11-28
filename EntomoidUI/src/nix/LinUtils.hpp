#pragma once

#include <memory>
#include "../Settings.hpp"

namespace entomoid {
    namespace utils {
        std::shared_ptr<void> inline platformGetCallback(size_t thisptr, void* fptr)
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
