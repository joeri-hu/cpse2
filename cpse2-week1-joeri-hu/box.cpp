#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "box.hpp"

box::box(
    sf::Vector2f const& position,
    sf::Vector2f const& size,
    sf::Color const& color
):
    drawable{rectangle},
    speed{}
{
    rectangle.setPosition(position);
    rectangle.setSize(size);
    rectangle.setFillColor(color);
}

void box::draw(sf::RenderWindow& window) const {
    window.draw(rectangle);
}

void box::move(sf::Vector2f const& delta) {
    rectangle.move(delta);
    speed = delta;
}

void box::invertMove() {
    rectangle.move(-speed);
}
