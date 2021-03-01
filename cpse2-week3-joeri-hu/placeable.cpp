#include <ostream>
#include <sfml/graphics.hpp>
#include "placeable.hpp"

placeable::placeable(sf::Drawable const& drawable) noexcept:
    placeable{drawable, {0, 0}}
{}

placeable::placeable(
    sf::Drawable const& drawable,
    sf::Vector2f const& center
) noexcept:
    center{center},
    drawable{drawable}
{}

auto placeable::draw(
    sf::RenderTarget& window,
    sf::RenderStates states
) const noexcept -> void {
    window.draw(drawable, states);
}

auto operator<<(std::ostream& output, placeable const& input) -> std::ostream& {
    return input.to_string(output);
}
