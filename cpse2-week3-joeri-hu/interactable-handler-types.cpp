#include "interactable-handler.hpp"
#include "interactable-handler.tpp"
#include "interactable-handler-types.hpp"

template class interactable_handler<positionable>;
template<>
action::contains_func const positionable::def_criteria = action::contains;
template<>
action::center_func const positionable::def_interaction = action::center;
