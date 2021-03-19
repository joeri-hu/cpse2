#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

class exit_program : std::exception {
public:
    exit_program() = default;
};

#endif
