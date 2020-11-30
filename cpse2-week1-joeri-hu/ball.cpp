#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "ball.hpp"

ball::ball(
    sf::Vector2f const& position,
    float size,
    sf::Color const& color
):
    drawable{circle},
    incidence{1, 1}
{
    circle.setPosition(position);
    circle.setRadius(size);
    circle.setFillColor(color);
}

bool ball::anyPointOverlaps(drawable const& other) const {
    auto radius = circle.getRadius();
    sf::Vector2f const& center{circle.getPosition() + radius};
    auto&& distance{center - other.getNearestPoint(center)};
    radius += other.getNearestPointOffset();
    distance *= distance;
    return (distance.x + distance.y) < (radius * radius);
}

sf::Vector2f ball::getNearestPoint(
    sf::Vector2f const& reference
) const {
    return circle.getPosition() + circle.getRadius();
}

float ball::getNearestPointOffset() const {
    return circle.getRadius();
}

void ball::draw(sf::RenderWindow& window) const {
    window.draw(circle);
}

void ball::update(sf::Vector2f const& delta) {
    circle.move(delta * incidence);
}

void ball::bounce(sf::Vector2f const& angle) {
    incidence *= angle;
}
