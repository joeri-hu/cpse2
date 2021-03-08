#ifndef EXPERIMENTAL_HPP
#define EXPERIMENTAL_HPP

#include <experimental/memory>

namespace ste {
    using namespace std::experimental;

    template<typename T, typename... Ts>
    inline auto make_observer(Ts&&... args) -> observer_ptr<T>;
}

#include "experimental.tpp"
#endif
