#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <sfml/graphics.hpp>
#include "interactable-handler.hpp"
#include "interactable-handler-types.hpp"
#include "placeable-factory.hpp"

class editor {
public:
    editor(
        sf::RenderWindow& window,
        std::string resource_file,
        sf::Color background_color
    ) noexcept;
    auto run() -> int;
private:
    interactable_handler<positionable> handler;
    placeable_factory factory;
    sf::RenderWindow& window;
    sf::Color bg_color;

    auto process_events() const noexcept -> void;
    auto interact() -> void;
    auto draw() const -> void;
};

#endif
