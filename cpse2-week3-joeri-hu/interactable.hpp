#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include <experimental/memory>
#include "experimental.hpp"
#include "placeable.hpp"

template<typename Fm, typename Fi>
class interactable {
public:
    explicit interactable(ste::observer_ptr<placeable> const& draw_obj) noexcept;
    interactable(
        ste::observer_ptr<placeable> const& draw_obj,
        Fm criteria,
        Fi interaction
    ) noexcept;
    template<typename... Ts>
    auto match(Ts&&... args) const noexcept;
    template<typename... Ts>
    auto interact(Ts&&... args) const noexcept;
    auto get_draw_object() const noexcept -> placeable const&;
private:
    static Fm const def_criteria;
    static Fi const def_interaction;
    std::unique_ptr<placeable> draw_obj;
    Fm criteria;
    Fi interaction;
    template<typename F, typename... Ts>
    constexpr auto invoke_action(F action, Ts&&... args) const noexcept;
};

#include "interactable.tpp"
#endif
