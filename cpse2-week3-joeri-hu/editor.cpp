#include <utility>
#include <cstdlib>
#include <sfml/graphics.hpp>

#include "interactable-handler.hpp"
#include "placeable-factory.hpp"
#include "editor.hpp"

editor::editor(
    sf::RenderWindow& window,
    std::string resource_file,
    sf::Color background_color
) noexcept:
    handler{window},
    factory{handler, std::move(resource_file)},
    window{window},
    bg_color{background_color}
{}

auto editor::run() -> int {
    if (not factory.import_resources()) {
        return EXIT_FAILURE;
    }
    while (window.isOpen()) {
        interact();
        draw();
        process_events();
    }
    return EXIT_SUCCESS;
}

auto editor::process_events() const noexcept -> void {
    for (sf::Event event; window.pollEvent(event);) {
        if (event.type == sf::Event::Closed
            or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
        ) {
            return window.close();
        }
    }
}

auto editor::interact() -> void {
    if (window.hasFocus()) {
        handler.interact();
    }
}

auto editor::draw() const -> void {
    window.clear(bg_color);
    handler.draw_all();
    window.display();
}
