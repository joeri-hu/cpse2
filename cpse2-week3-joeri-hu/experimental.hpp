#ifndef EXPERIMENTAL_HPP
#define EXPERIMENTAL_HPP

#include <utility>
#include <experimental/memory>

namespace ste {
    using namespace std::experimental;

    template<typename T, typename... Ts>
    inline auto make_observer(Ts&&... args) -> observer_ptr<T> {
        return observer_ptr<T>(new T(std::forward<Ts>(args)...));
    }
}

#endif
