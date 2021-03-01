#include <sfml/graphics.hpp>
#include "utilities.hpp"
#include "figure.hpp"

figure::figure(sf::Shape& shape) noexcept:
    placeable{shape},
    shape{shape}
{}

figure::figure(sf::Shape& shape, sf::Vector2f const& center) noexcept:
    placeable{shape, center},
    shape{shape}
{}

auto figure::contains(sf::Vector2f const& target) const noexcept -> bool {
    return shape.getGlobalBounds().contains(target);
}

auto figure::set_center_pos(sf::Vector2f const& position) noexcept -> void {
    shape.setPosition(position - center);
}
