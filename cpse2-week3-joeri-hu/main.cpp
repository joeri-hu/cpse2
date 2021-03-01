#include <sfml/graphics.hpp>
#include "config.hpp"
#include "editor.hpp"

auto main() -> int {
    auto window = sf::RenderWindow{
        {screen::height, screen::width},
        screen::title
    };
    window.setFramerateLimit(screen::fps);
    return editor{window, file::objects, screen::color}.run();
}
