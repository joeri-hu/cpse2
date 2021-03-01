#include <utility>
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
    factory.import_resources();

    while (window.isOpen()) {
        if (is_closing_initiated()) {
            window.close();
            return 0;
        }
        interact();
        draw();
    }
    return 1;
}

auto editor::is_closing_initiated() const noexcept -> bool {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        return true;
    }
    for (sf::Event event; window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
            return true;
        }
    }
    return false;
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
