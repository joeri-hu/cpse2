#ifndef PLACEABLE_HANDLER_HPP
#define PLACEABLE_HANDLER_HPP

#include <ostream>
#include <experimental/memory>
#include <sfml/graphics.hpp>

#include "experimental.hpp"
#include "placeable.hpp"

class placeable_handler {
public:
    placeable_handler(placeable_handler const&) = delete;
    placeable_handler& operator=(placeable_handler const&) = delete;
    placeable_handler(placeable_handler&&) = delete;
    placeable_handler& operator=(placeable_handler&&) = delete;

    virtual auto add(ste::observer_ptr<placeable> const& draw_obj) -> bool = 0;
    virtual auto draw_all() const -> void = 0;
    virtual auto print_all(std::ostream& output) const -> void = 0;
protected:
    explicit placeable_handler(sf::RenderWindow& window) noexcept;
    placeable_handler() = default;
    ~placeable_handler() = default;
    sf::RenderWindow& window;
};

#endif
