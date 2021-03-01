#include <ostream>
#include <sfml/graphics.hpp>

#include "overloads.hpp"
#include "utilities.hpp"
#include "figure.hpp"
#include "rect.hpp"

rect::rect(
    sf::Vector2f const& start,
    sf::Vector2f const& end,
    sf::Color const& color
) noexcept:
    figure{shape, (end - start) / 2.0f},
    shape{util::abs_diff_from_points(start, end)}
{
    shape.setPosition(start);
    shape.setFillColor(color);
}

auto rect::to_string(std::ostream& output) const -> std::ostream& {
    auto const& position = shape.getPosition();
    return output << position << " rect " << position + shape.getSize()
        << ' ' << shape.getFillColor();
}
