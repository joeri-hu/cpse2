#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class wall: public drawable {
private:
    sf::RectangleShape rectangle;
public:
    wall(
        sf::Vector2f const& position,
        sf::Vector2f const& size,
        sf::Color const& color = sf::Color::White
    );
    virtual void draw(sf::RenderWindow& window) const override;
};

#endif
