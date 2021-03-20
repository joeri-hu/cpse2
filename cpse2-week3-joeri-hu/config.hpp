#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <sfml/graphics.hpp>

inline namespace config {
    namespace screen {
        inline constexpr auto title = "editor";
        inline constexpr auto height = 576;
        inline constexpr auto width = 1024;
        inline constexpr auto fps = 60;
        inline auto const color = sf::Color{25, 25, 25};
        inline auto const mode = sf::VideoMode{width, height};
        inline auto const size = sf::Vector2f{width, height};
    }
    namespace resource {
        inline constexpr auto objects = "objects.txt";
    }
}

#endif
