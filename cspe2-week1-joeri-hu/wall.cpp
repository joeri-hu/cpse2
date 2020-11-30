#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "wall.hpp"

wall::wall(
    sf::Vector2f const& position,
    sf::Vector2f const& size,
    sf::Color const& color
):
    drawable{rectangle}
{
    rectangle.setPosition(position);
    rectangle.setSize(size);
    rectangle.setFillColor(color);
}

void wall::draw(sf::RenderWindow& window) const {
    window.draw(rectangle);
}
