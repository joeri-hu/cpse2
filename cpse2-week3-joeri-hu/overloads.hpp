#ifndef OVERLOADS_HPP
#define OVERLOADS_HPP

#include <ostream>
#include <sfml/graphics.hpp>

namespace sf {
    template<typename T>
    inline auto operator*=(
        sf::Vector2<T>& left,
        sf::Vector2<T> const& right
    ) noexcept -> sf::Vector2<T>&;
    template<typename T>
    inline auto operator*(
        sf::Vector2<T> left,
        sf::Vector2<T> const& right
    ) noexcept -> sf::Vector2<T>;
    template<typename T>
    inline auto operator<(
        sf::Vector2<T> const& left,
        sf::Vector2<T> const& right
    ) noexcept -> bool;
    template<typename T>
    inline auto operator<=(
        sf::Vector2<T> const& left,
        sf::Vector2<T> const& right
    ) noexcept -> bool;
    template<typename T>
    inline auto operator>(
        sf::Vector2<T> const& left,
        sf::Vector2<T> const& right
    ) noexcept -> bool;
    template<typename T>
    inline auto operator>=(
        sf::Vector2<T> const& left,
        sf::Vector2<T> const& right
    ) noexcept -> bool;
}

template<typename T>
inline auto operator<<(
    std::ostream& output,
    sf::Vector2<T> const& input
) -> std::ostream&;
// seems to help with auto return type deduction
template<typename T = void>
inline auto operator<<(
    std::ostream& output,
    sf::Color const& input
) -> std::ostream&;

#include "overloads.tpp"
#endif
