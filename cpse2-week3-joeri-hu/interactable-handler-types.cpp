#include "interactable-handler.hpp"
#include "interactable-handler.tpp"
#include "interactable-handler-types.hpp"

template class interactable_handler<positionable>;
template<>
decltype(positionable::criteria_def)
    positionable::criteria_def = action::contains;
template<>
decltype(positionable::interaction_def)
    positionable::interaction_def = action::center;
