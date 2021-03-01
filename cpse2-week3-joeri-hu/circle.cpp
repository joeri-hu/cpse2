#include <ostream>
#include <sfml/graphics.hpp>

#include "overloads.hpp"
#include "utilities.hpp"
#include "figure.hpp"
#include "circle.hpp"

circle::circle(
    sf::Vector2f const& position,
    sf::Color const& color,
    float radius
) noexcept:
    figure{shape, {radius, radius}},
    shape{radius}
{
    shape.setPosition(position);
    shape.setFillColor(color);
}

auto circle::contains(sf::Vector2f const& target) const noexcept -> bool {
    return figure::contains(target)
        and util::is_within_reach(
            shape.getRadius(), shape.getPosition() + center, target);
}

auto circle::to_string(std::ostream& output) const -> std::ostream& {
    return output << shape.getPosition() << " circle "
        << shape.getFillColor() << ' ' << shape.getRadius();
}
