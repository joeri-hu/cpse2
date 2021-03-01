#include <ostream>
#include <algorithm>
#include <experimental/memory>
#include <sfml/graphics.hpp>

#include "experimental.hpp"
#include "utilities.hpp"
#include "placeable.hpp"
#include "interactable.hpp"
#include "interactable-handler.hpp"

template<typename T>
interactable_handler<T>::interactable_handler(
    sf::RenderWindow& window
) noexcept:
    placeable_handler{window},
    selection{interactables.end()},
    window_rect{{0, 0}, sf::Vector2f{window.getSize()}}
{}

template<typename T>
auto interactable_handler<T>::add(ste::observer_ptr<placeable> const& draw_obj) -> bool {
    if (is_target_selected()) {
        return false;
    }
    interactables.emplace_back(draw_obj);
    reset_selection();
    return true;
}

template<typename T>
auto interactable_handler<T>::is_target_selected() const noexcept -> bool {
    return selection not_eq interactables.end();
}

template<typename T>
auto interactable_handler<T>::reset_selection() noexcept -> void {
    selection = interactables.end();
}

template<typename T>
auto interactable_handler<T>::interact() -> void {
    if (is_target_selected()) {
        handle_interaction();
    } else if (is_interaction_active()) {
        find_selection();
        bring_selection_to_front();
    }
}

template<typename T>
auto interactable_handler<T>::handle_interaction() noexcept -> void {
    if (is_interaction_active()) {
        selection->interact(restrict_position(util::get_mouse_pos(window)));
    } else {
        reset_selection();
    }
}

template<typename T>
auto interactable_handler<T>::is_interaction_active() const noexcept -> bool {
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

template<typename T>
auto interactable_handler<T>::restrict_position(
    sf::Vector2f position
) const noexcept -> sf::Vector2f {
    position.x = std::clamp(position.x, window_rect.start.x, window_rect.end.x);
    position.y = std::clamp(position.y, window_rect.start.y, window_rect.end.y);
    return position;
}

template<typename T>
auto interactable_handler<T>::find_selection() -> void {
    auto const mouse_pos = util::get_mouse_pos(window);
    selection = std::find_if(interactables.begin(), interactables.end(),
        [&mouse_pos = std::as_const(mouse_pos)]
        (auto const& interactable) -> bool {
            return interactable.match(mouse_pos);
        }
    );
}

template<typename T>
auto interactable_handler<T>::bring_selection_to_front() -> void {
    if (is_target_selected()) {
        std::iter_swap(selection, interactables.begin());
        selection = interactables.begin();
    }
}

template<typename T>
auto interactable_handler<T>::draw_all() const -> void {
    std::for_each(interactables.crbegin(), interactables.crend(),
        [&](auto const& interactable) -> void {
            window.draw(interactable.get_draw_object());
        }
    );
}

template<typename T>
auto interactable_handler<T>::print_all(std::ostream& output) const -> void {
    std::for_each(interactables.cbegin(), interactables.cend(),
        [&output](auto const& interactable) -> void {
            output << interactable.get_draw_object() << std::endl;
        }
    );
}
