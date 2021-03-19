#ifndef MARK_HPP
#define MARK_HPP

#include <cstdint>

namespace mark {
    enum class pos : int8_t {
        square1,
        square2,
        square3,
        square4,
        square5,
        square6,
        square7,
        square8,
        square9
    };
    enum class type : int8_t {
        none,
        cross,
        nought,
    };
}

#endif
