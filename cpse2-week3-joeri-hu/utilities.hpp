#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <sfml/graphics.hpp>

namespace util {
inline namespace screen {
    inline auto get_mouse_pos(sf::RenderWindow const& window) noexcept -> sf::Vector2f;
} inline namespace object {
    inline auto get_color_table() noexcept;
} inline namespace dimension {
    template<typename T>
    inline auto center_origin(T& drawable) noexcept -> void;
    template<typename T>
    inline auto get_center(T const& drawable) noexcept -> sf::Vector2f;
    template<typename T>
    inline auto get_size(T const& drawable) noexcept -> sf::Vector2f;
    template<typename T, typename Te = float>
    inline auto get_extended_bounds(T& vertices, Te extension = 1) noexcept;
    template<typename T>
    inline auto abs_diff_from_points(
        sf::Vector2<T> const& start,
        sf::Vector2<T> const& end
    ) noexcept -> sf::Vector2<T>;
} inline namespace collision {
    template<typename T>
    inline auto intersects_projectively(
        sf::Vector2<T> const& target,
        sf::Vector2<T> const& start,
        sf::Vector2<T> const& end,
        T margin = 128
    ) noexcept -> bool;
    template<typename T>
    constexpr auto is_within_bounds(
        T value,
        T min,
        T max
    ) noexcept -> bool;
    template<typename T>
    inline auto is_within_bounds(
        sf::Vector2<T> value,
        sf::Vector2<T> min,
        sf::Vector2<T> max
    ) noexcept -> bool;
    template<typename T>
    constexpr auto is_within_inverted_bounds(
        T value,
        T min,
        T max
    ) noexcept -> bool;
    template<typename T>
    inline auto is_within_reach(
        T reach,
        sf::Vector2<T> const& start,
        sf::Vector2<T> const& end
    ) noexcept -> bool;
}
}

#include "utilities.tpp"
#endif
