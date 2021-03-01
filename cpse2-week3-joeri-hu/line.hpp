#ifndef LINE_HPP
#define LINE_HPP

#include <ostream>
#include <sfml/graphics.hpp>
#include "placeable.hpp"

class line final: public placeable {
public:
    line(
        sf::Vector2f const& start,
        sf::Vector2f const& end,
        sf::Color const& color
    ) noexcept;
    virtual auto to_string(std::ostream& output) const -> std::ostream& override;
private:
    sf::VertexArray vertices;
    virtual auto contains(sf::Vector2f const& target) const noexcept -> bool override;
    virtual auto set_center_pos(sf::Vector2f const& position) noexcept -> void override;
    using vertex = struct {enum {start, end};};
};

#endif
