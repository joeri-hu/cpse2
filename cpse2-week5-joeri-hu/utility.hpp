#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <map>
#include <chrono>
#include <thread>
#include <utility>
#include <algorithm>

namespace util {
inline namespace time {
    inline auto wait_for_sec(int seconds) -> void {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }
} inline namespace lookup {
    template<typename T>
    inline auto find_key(T const& map, typename T::mapped_type const& value)
    -> typename T::const_iterator {
        return std::find_if(map.cbegin(), map.cend(),
        [&value = std::as_const(value)]
        (auto const& entry) -> bool {
            return entry.second == value;
        });
    }
}
}

#endif
