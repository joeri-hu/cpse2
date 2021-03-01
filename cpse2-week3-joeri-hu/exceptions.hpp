#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <exception>

class end_of_file : public std::exception {
public:
    end_of_file() = default;
};

class unexpected_end_of_file : public std::exception {
public:
    unexpected_end_of_file() = default;
};

class unknown_shape : public std::exception {
public:
    explicit unknown_shape(std::string const& shape) noexcept;
    virtual auto what() const noexcept -> char const* override;
private:
    std::string msg;
};

class unknown_color : public std::exception {
public:
    explicit unknown_color(std::string const& color) noexcept;
    virtual auto what() const noexcept -> char const* override;
private:
    std::string msg;
};

class invalid_position : public std::exception {
public:
    invalid_position();
    explicit invalid_position(char symbol) noexcept;
    virtual auto what() const noexcept -> char const* override;
private:
    std::string msg;
};

#endif
