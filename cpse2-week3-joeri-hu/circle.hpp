#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <ostream>
#include <sfml/graphics.hpp>
#include "figure.hpp"

class circle final: public figure {
public:
    circle(sf::Vector2f const& position, sf::Color const& color, float radius) noexcept;
    auto to_string(std::ostream& output) const -> std::ostream& override;
private:
    sf::CircleShape shape;
    auto contains(sf::Vector2f const& target) const noexcept -> bool override;
};

#endif
