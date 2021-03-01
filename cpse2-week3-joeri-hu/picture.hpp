#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <string>
#include <ostream>
#include <sfml/graphics.hpp>
#include "placeable.hpp"

class picture final: public placeable {
public:
    picture(sf::Vector2f const& position, std::string filename);
    virtual auto to_string(std::ostream& output) const -> std::ostream& override;
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string filename;
    virtual auto contains(sf::Vector2f const& target) const noexcept -> bool override;
    virtual auto set_center_pos(sf::Vector2f const& position) noexcept -> void override;
};

#endif
