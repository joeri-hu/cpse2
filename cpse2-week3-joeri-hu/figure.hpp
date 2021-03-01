#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <sfml/graphics.hpp>
#include "placeable.hpp"

class figure : public placeable {
public:
    virtual ~figure() = default;
    figure(figure const&) = delete;
    figure& operator=(figure const&) = delete;
    figure(figure&&) = delete;
    figure& operator=(figure&&) = delete;
protected:
    explicit figure(sf::Shape& shape) noexcept;
    figure(sf::Shape& shape, sf::Vector2f const& center) noexcept;
    virtual auto contains(sf::Vector2f const& target) const noexcept -> bool override;
private:
    sf::Shape& shape;
    virtual auto set_center_pos(sf::Vector2f const& position) noexcept -> void override;
};

#endif
