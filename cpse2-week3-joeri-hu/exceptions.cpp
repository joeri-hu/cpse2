#include <string>
#include <exception>
#include "exceptions.hpp"

unknown_shape::unknown_shape(std::string const& shape) noexcept:
    msg{"object shape not recognized: '" + shape + "'"}
{}

auto unknown_shape::what() const noexcept -> char const* {
    return msg.data();
}

unknown_color::unknown_color(std::string const& color) noexcept:
    msg{"color not recognized: '" + color + "'"}
{}

auto unknown_color::what() const noexcept -> char const* {
    return msg.data();
}

invalid_position::invalid_position():
    msg{"numeric value expected"}
{}

invalid_position::invalid_position(char symbol) noexcept:
    msg{std::string("symbol '") + symbol + "' was unexpected at this time"}
{}

auto invalid_position::what() const noexcept -> char const* {
    return msg.data();
}
