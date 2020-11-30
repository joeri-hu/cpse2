#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class ball: public drawable {
private:
    sf::CircleShape circle;
    sf::Vector2f incidence;
public:
    ball(
        sf::Vector2f const& position,
        float size = 30,
        sf::Color const& color = sf::Color::White
    );
    virtual bool anyPointOverlaps(drawable const& other) const override;
    virtual sf::Vector2f getNearestPoint(
        sf::Vector2f const& reference
    ) const override;
    virtual float getNearestPointOffset() const override;
    virtual void draw(sf::RenderWindow& window) const override;
    void update(sf::Vector2f const& delta);
    void bounce(sf::Vector2f const& delta);
};

#endif
