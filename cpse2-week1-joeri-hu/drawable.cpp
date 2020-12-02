#include <vector>
#include <SFML/Graphics.hpp>
#include "drawable.hpp"

drawable::drawable(sf::Shape const& shape):
    shape{shape}
{
    allDrawables.push_back(this);
}

void drawable::drawAll(sf::RenderWindow& window) {
    for (auto const& drawable : allDrawables) {
        drawable->draw(window);
    }
}

bool drawable::anyObjectOverlaps(drawable const& target) {
    for (auto const& drawable : allDrawables) {
        if (drawable == &target) {
            continue;
        }
        bool const overlaps{target.shape.getGlobalBounds()
            .intersects(drawable->shape.getGlobalBounds())
        };
        if (overlaps) {
            return target.anyPointOverlaps(*drawable)
                and drawable->anyPointOverlaps(target);
        }
    }
    return false;
}

bool drawable::anyPointOverlaps(drawable const& other) const {
    return true;
}

sf::Vector2f drawable::getNearestPoint(
    sf::Vector2f const& reference
) const {
    auto const& bounds = shape.getGlobalBounds();
    return {
        std::clamp(reference.x, bounds.left, bounds.left + bounds.width),
        std::clamp(reference.y, bounds.top, bounds.top + bounds.height)
    };
}

float drawable::getNearestPointOffset() const {
    return 0;
}

void drawable::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f operator+(
    sf::Vector2f const& left,
    float const right
) {
    return {left.x + right, left.y + right};
}

sf::Vector2f operator*(
    sf::Vector2f const& left,
    sf::Vector2f const& right
) {
    return {left.x * right.x, left.y * right.y};
}

sf::Vector2f const& operator*=(
    sf::Vector2f& left,
    sf::Vector2f const& right
) {
    left.x *= right.x;
    left.y *= right.y;
    return left;
}
