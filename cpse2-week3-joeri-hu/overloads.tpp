#include <ostream>
#include <sfml/graphics.hpp>

#include "utilities.hpp"
#include "overloads.hpp"

template<typename T>
inline auto operator<<(
    std::ostream& output,
    sf::Vector2<T> const& input
) -> std::ostream& {
    return output << '(' << input.x << ',' << input.y << ')';
}

template<typename T>
inline auto operator<<(
    std::ostream& output,
    sf::Color const& input
) -> std::ostream& {
    for (auto const& option : util::get_color_table()) {
        if (option.color == input) {
            return output << option.name;
        }
    }
    return output;
}

namespace sf {
    template<typename T>
    inline auto operator*(
        sf::Vector2<T> left,
        sf::Vector2<T> const& right
    ) noexcept -> sf::Vector2<T> {
        left *= right;
        return left;
    }

    template<typename T>
    inline auto operator*=(
        sf::Vector2<T>& left,
        sf::Vector2<T> const& right
    ) noexcept -> sf::Vector2<T>& {
        left.x *= right.x;
        left.y *= right.y;
        return left;
    }

    template<typename T>
    inline auto operator<(
        sf::Vector2<T> const& left,
        sf::Vector2<T> const& right
    ) noexcept -> bool {
        return left.x < right.x and left.y < right.y;
    }

    template<typename T>
    inline auto operator<=(
        sf::Vector2<T> const& left,
        sf::Vector2<T> const& right
    ) noexcept -> bool {
        return left < right or left == right;
    }

    template<typename T>
    inline auto operator>(
        sf::Vector2<T> const& left,
        sf::Vector2<T> const& right
    ) noexcept -> bool {
        return left.x > right.x and left.y > right.y;
    }

    template<typename T>
    inline auto operator>=(
        sf::Vector2<T> const& left,
        sf::Vector2<T> const& right
    ) noexcept -> bool {
        return left > right or left == right;
    }
}
