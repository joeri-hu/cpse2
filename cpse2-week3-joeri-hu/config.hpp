#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <sfml/graphics.hpp>

inline namespace config {
    namespace screen {
        constexpr auto title = "Factory";
        constexpr auto height = 1024;
        constexpr auto width = 576;
        constexpr auto fps = 60;
        inline auto const color = sf::Color{25, 25, 25};
        inline auto const size = sf::Vector2f{height, width};
    }
    namespace file {
        constexpr auto objects = "objects.txt";
    }
}

#endif
