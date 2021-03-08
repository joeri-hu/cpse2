#include <utility>
#include <type_traits>
#include <experimental/memory>

#include "experimental.hpp"
#include "interactable.hpp"

template<typename Fm, typename Fi>
interactable<Fm, Fi>::interactable(
    ste::observer_ptr<placeable> const& draw_obj
) noexcept:
    interactable{draw_obj, criteria_def, interaction_def}
{}

template<typename Fm, typename Fi>
template<typename M, typename I>
interactable<Fm, Fi>::interactable(
    ste::observer_ptr<placeable> const& draw_obj,
    M&& criteria,
    I&& interaction
) noexcept:
    draw_obj{draw_obj.get()},
    criteria{std::forward<M>(criteria)},
    interaction{std::forward<I>(interaction)}
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
auto interactable<Fm, Fi>::invoke_action(F&& action, Ts&&... args) const noexcept {
    if constexpr (std::is_member_function_pointer_v<std::decay_t<F>>) {
        return (*draw_obj.*action)(std::forward<Ts>(args)...);
    } else {
        return action(std::forward<Ts>(args)...);
    }
}

template<typename Fm, typename Fi>
auto interactable<Fm, Fi>::get_draw_object() const noexcept -> placeable const& {
    return *draw_obj;
}
