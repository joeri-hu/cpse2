#ifndef INTERACTABLE_HANDLER_HPP
#define INTERACTABLE_HANDLER_HPP

#include <vector>
#include <ostream>
#include <experimental/memory>
#include <sfml/graphics.hpp>

#include "placeable-handler.hpp"
#include "experimental.hpp"
#include "interactable.hpp"
#include "placeable.hpp"

template<typename T>
class interactable_handler : public placeable_handler {
public:
    explicit interactable_handler(sf::RenderWindow& window) noexcept;
    auto interact() -> void;
    virtual auto add(ste::observer_ptr<placeable> const& draw_obj) -> bool override;
    virtual auto draw_all() const -> void override;
    virtual auto print_all(std::ostream& output) const -> void override;
private:
    std::vector<T> interactables;
    typename decltype(interactables)::iterator selection;
    struct {sf::Vector2f start; sf::Vector2f end;} const window_rect;

    auto is_target_selected() const noexcept -> bool;
    auto is_interaction_active() const noexcept -> bool;
    auto handle_interaction() noexcept -> void;
    auto restrict_position(sf::Vector2f position) const noexcept -> sf::Vector2f;
    auto find_selection() -> void;
    auto reset_selection() noexcept -> void;
    auto bring_selection_to_front() -> void;
};

#endif
