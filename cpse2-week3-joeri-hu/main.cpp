#include <sfml/graphics.hpp>
#include "config.hpp"
#include "editor.hpp"

auto main() -> int {
    auto window = sf::RenderWindow{screen::mode, screen::title};
    window.setFramerateLimit(screen::fps);
    return editor{window, resource::objects, screen::color}.run();
}
