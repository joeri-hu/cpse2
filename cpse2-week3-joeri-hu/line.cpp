#include <ostream>
#include <sfml/graphics.hpp>

#include "overloads.hpp"
#include "utilities.hpp"
#include "placeable.hpp"
#include "line.hpp"

line::line(
    sf::Vector2f const& start,
    sf::Vector2f const& end,
    sf::Color const& color
) noexcept:
    placeable{vertices, start + ((end - start) / 2.0f)},
    vertices{sf::Lines}
{
    vertices.append({start, color});
    vertices.append({end, color});
}

auto line::contains(sf::Vector2f const& target) const noexcept -> bool {
    return util::get_extended_bounds(vertices).contains(target)
        and util::intersects_projectively(target,
            vertices[vertex::start].position,
            vertices[vertex::end].position);
}

auto line::set_center_pos(sf::Vector2f const& position) noexcept -> void {
    auto const distance = center - position;
    vertices[vertex::start].position -= distance;
    vertices[vertex::end].position -= distance;
    center = position;
}

auto line::to_string(std::ostream& output) const -> std::ostream& {
    return output << vertices[vertex::start].position << " line "
        << vertices[vertex::end].position << ' ' << vertices[vertex::end].color;
}
