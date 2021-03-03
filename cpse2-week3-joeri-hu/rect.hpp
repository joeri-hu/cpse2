#ifndef RECT_HPP
#define RECT_HPP

#include <ostream>
#include <sfml/graphics.hpp>
#include "figure.hpp"

class rect final: public figure {
public:
    rect(
        sf::Vector2f const& start,
        sf::Vector2f const& end,
        sf::Color const& color
    ) noexcept;
    auto to_string(std::ostream& output) const -> std::ostream& override;
private:
    sf::RectangleShape shape;
};

#endif
