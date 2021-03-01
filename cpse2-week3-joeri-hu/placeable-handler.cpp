#include <sfml/graphics.hpp>
#include "placeable-handler.hpp"

placeable_handler::placeable_handler(sf::RenderWindow& window) noexcept:
    window{window}
{}
