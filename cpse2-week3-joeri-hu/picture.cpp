#include <string>
#include <utility>
#include <ostream>
#include <exception>
#include <sfml/graphics.hpp>

#include "overloads.hpp"
#include "utilities.hpp"
#include "placeable.hpp"
#include "picture.hpp"

picture::picture(sf::Vector2f const& position, std::string filename):
    placeable{sprite},
    filename{std::move(filename)}
{
    if (not texture.loadFromFile(this->filename)) {
        throw std::runtime_error(
            "unable to load texture '" + this->filename + "' :(");
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    center = sf::Vector2f{texture.getSize() / 2u};
}

auto picture::contains(sf::Vector2f const& target) const noexcept -> bool {
    return sprite.getGlobalBounds().contains(target);
}

auto picture::set_center_pos(sf::Vector2f const& position) noexcept -> void {
    sprite.setPosition(position - center);
}

auto picture::to_string(std::ostream& output) const -> std::ostream& {
    return output << sprite.getPosition() << " picture " << filename;
}
