#ifndef BOX_HPP
#define BOX_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class box: public drawable {
private:
    sf::RectangleShape rectangle;
    sf::Vector2f speed;
public:
    box(
        sf::Vector2f const& position,
        sf::Vector2f const& size,
        sf::Color const& color = sf::Color::White
    );
    void move(sf::Vector2f const& delta);
    void invertMove();
};

#endif
