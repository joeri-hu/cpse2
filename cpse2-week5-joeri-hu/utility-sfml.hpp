#ifndef UTILITY_SFML_HPP
#define UTILITY_SFML_HPP

#include <map>
#include <utility>
#include <algorithm>
#include <sfml/graphics.hpp>

#include <iostream>

namespace util {
inline namespace screen {
    inline auto get_mouse_pos(sf::RenderWindow const& window) -> sf::Vector2f {
        return window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }
}
inline namespace collision {
    template<typename T, typename V>
    inline auto find_target(T const& map, V const& target)
    -> typename T::const_iterator {
        return std::find_if(map.cbegin(), map.cend(),
            [&target = std::as_const(target)]
            (auto const& entry) -> bool {
                return entry.second.getGlobalBounds().contains(target);
            }
        );
    }
}
}

#endif
