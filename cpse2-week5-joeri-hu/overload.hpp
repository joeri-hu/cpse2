#ifndef OVERLOAD_HPP
#define OVERLOAD_HPP

#include <sfml/graphics.hpp>

namespace sf {
    template<typename T>
    inline auto operator*(
        sf::Vector2<T> left,
        sf::Vector2<T> const& right
    ) -> sf::Vector2<T> {
        left *= right;
        return left;
    }

    template<typename T>
    inline auto operator*=(
        sf::Vector2<T>& left,
        sf::Vector2<T> const& right
    ) -> sf::Vector2<T>& {
        left.x *= right.x;
        left.y *= right.y;
        return left;
    }
}

#endif
