#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <map>
#include <utility>
#include <algorithm>

namespace util {
inline namespace lookup {
    template<typename T>
    inline auto find_key(T const& map, typename T::mapped_type const& value)
    -> typename T::const_iterator {
        return std::find_if(map.cbegin(), map.cend(),
            [&value = std::as_const(value)]
            (auto const& entry) -> bool {
                return entry.second == value;
            }
        );
    }
}
}

#endif
