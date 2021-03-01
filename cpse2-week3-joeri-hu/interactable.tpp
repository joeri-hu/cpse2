#include <utility>
#include <type_traits>
#include <experimental/memory>

#include "experimental.hpp"
#include "interactable.hpp"

template<typename Fm, typename Fi>
interactable<Fm, Fi>::interactable(
    ste::observer_ptr<placeable> const& draw_obj
) noexcept:
    interactable{draw_obj, def_criteria, def_interaction}
{}

template<typename Fm, typename Fi>
interactable<Fm, Fi>::interactable(
    ste::observer_ptr<placeable> const& draw_obj,
    Fm criteria,
    Fi interaction
) noexcept:
    draw_obj{draw_obj.get()},
    criteria{criteria},
    interaction{interaction}
{}

template<typename Fm, typename Fi>
template<typename... Ts>
auto interactable<Fm, Fi>::match(Ts&&... args) const noexcept {
    return invoke_action(criteria, args...);
}

template<typename Fm, typename Fi>
template<typename... Ts>
auto interactable<Fm, Fi>::interact(Ts&&... args) const noexcept {
    return invoke_action(interaction, args...);
}

template<typename Fm, typename Fi>
template<typename F, typename... Ts>
constexpr auto interactable<Fm, Fi>::invoke_action(
    F action,
    Ts&&... args
) const noexcept {
    if constexpr (std::is_member_function_pointer_v<F>) {
        return (*draw_obj.*action)(std::forward<Ts>(args)...);
    } else {
        return action(std::forward<Ts>(args)...);
    }
}

template<typename Fm, typename Fi>
auto interactable<Fm, Fi>::get_draw_object() const noexcept -> placeable const& {
    return *draw_obj;
}
