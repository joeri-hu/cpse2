#ifndef INTERACTABLE_HANDLER_TYPES_HPP
#define INTERACTABLE_HANDLER_TYPES_HPP

#include <type_traits>
#include "placeable.hpp"
#include "interactable.hpp"

namespace {
    namespace action {
        constexpr auto contains = &placeable::contains;
        constexpr auto center = &placeable::set_center_pos;

        template<auto A>
        using type_of = std::decay_t<decltype(A)>;
        using contains_func = type_of<contains>;
        using center_func = type_of<center>;
    }
    using positionable = interactable<action::contains_func, action::center_func>;
}

#endif
