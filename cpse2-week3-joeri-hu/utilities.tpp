#include <cmath>
#include <algorithm>
#include <sfml/graphics.hpp>

#include "overloads.hpp"
#include "utilities.hpp"

namespace util {
inline namespace screen {
    inline auto get_mouse_pos(
        sf::RenderWindow const& window
    ) noexcept -> sf::Vector2f {
        return window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }
} inline namespace object {
    inline auto get_color_table() noexcept {
        using data = struct {std::string_view name; sf::Color color;};
        return std::array{
            data{"red", sf::Color::Red},
            data{"green", sf::Color::Green},
            data{"blue", sf::Color::Blue},
            data{"yellow", sf::Color::Yellow},
            data{"cyan", sf::Color::Cyan},
            data{"magenta", sf::Color::Magenta},
            data{"white", sf::Color::White}
        };
    }
} inline namespace dimension {
    template<typename T>
    inline auto center_origin(T& drawable) noexcept -> void {
        drawable.setOrigin(get_center(drawable));
    }

    template<typename T>
    inline auto get_center(T const& drawable) noexcept -> sf::Vector2f {
        return get_size(drawable) / 2.0f;
    }

    template<typename T>
    inline auto get_size(T const& drawable) noexcept -> sf::Vector2f {
        auto const bounds = drawable.getGlobalBounds();
        return {bounds.width, bounds.height};
    }

    template<typename T, typename Te>
    inline auto get_extended_bounds(T& vertices, Te extension) noexcept {
        auto bounds = vertices.getBounds();
        bounds.width += extension;
        bounds.height += extension;
        return bounds;
    }

    template<typename T>
    inline auto abs_diff_from_points(
        sf::Vector2<T> const& start,
        sf::Vector2<T> const& end
    ) noexcept -> sf::Vector2<T> {
        auto const diff = start - end;
        return {std::abs(diff.x), std::abs(diff.y)};
    }
} inline namespace collision {
    template<typename T>
    inline auto intersects_projectively(
        sf::Vector2<T> const& target,
        sf::Vector2<T> const& start,
        sf::Vector2<T> const& end,
        T margin
    ) noexcept -> bool {
        auto const dist1 = target - start;
        auto const dist2 = end - start;
        auto const cross = (dist1.x * dist2.y) - (dist1.y * dist2.x);
        return is_within_bounds(cross, -margin, margin);
    }

    template<typename T>
    constexpr auto is_within_bounds(
        T value,
        T min,
        T max
    ) noexcept -> bool {
        return value == std::clamp(value, min, max);
    }

    template<typename T>
    inline auto is_within_bounds(
        sf::Vector2<T> value,
        sf::Vector2<T> min,
        sf::Vector2<T> max
    ) noexcept -> bool {
        return is_within_bounds(value.x, min.x, max.x)
            and is_within_bounds(value.y, min.y, max.y);
    }

    template<typename T>
    constexpr auto is_within_inverted_bounds(
        T value,
        T min,
        T max
    ) noexcept -> bool {
        return is_within_bounds(value, max, min);
    }

    template<typename T>
    inline auto is_within_reach(
        T reach,
        sf::Vector2<T> const& start,
        sf::Vector2<T> const& end
    ) noexcept -> bool {
        auto dist = end - start;
        dist *= dist;
        return (dist.x + dist.y) < (reach * reach);
    }
}
}
