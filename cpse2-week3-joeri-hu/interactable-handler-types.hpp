#ifndef INTERACTABLE_HANDLER_TYPES_HPP
#define INTERACTABLE_HANDLER_TYPES_HPP

#include <type_traits>
#include "placeable.hpp"
#include "interactable.hpp"

namespace {
    namespace action {
        constexpr auto contains = &placeable::contains;
        constexpr auto center = &placeable::set_center_pos;

        template<typename T, typename R>
        using type_of = std::decay_t<std::conditional_t<
            std::is_swappable_v<std::decay_t<T>>, T, R>>;
        using contains_func = type_of<decltype(contains), decltype(std::ref(contains))>;
        using center_func = type_of<decltype(center), decltype(std::ref(center))>;
    }
    using positionable = interactable<action::contains_func, action::center_func>;
}

#endif
