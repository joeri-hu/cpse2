#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class drawable {
private:
    inline static std::vector<drawable*> allDrawables;
    sf::Shape const& shape;
public:
    drawable(sf::Shape const& shape);
    static void drawAll(sf::RenderWindow& window);
    static bool anyObjectOverlaps(drawable const& target);
    virtual bool anyPointOverlaps(drawable const& other) const;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual sf::Vector2f getNearestPoint(sf::Vector2f const& reference) const;
    virtual float getNearestPointOffset() const;
};

sf::Vector2f operator+(
    sf::Vector2f const& left,
    float const right
);
sf::Vector2f operator*(
    sf::Vector2f const& left,
    sf::Vector2f const& right
);
sf::Vector2f const& operator*=(
    sf::Vector2f& left,
    sf::Vector2f const& right
);

#endif
