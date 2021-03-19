#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "game-logic.hpp"

class command {
public:
    command(command const&) = default;
    command& operator=(command const&) = default;
    command(command&&) = default;
    command& operator=(command&&) = default;

    virtual auto execute(game_logic& game) const -> void = 0;
    virtual auto undo(game_logic& game) const -> void = 0;
protected:
    command() = default;
    ~command() = default;
};

#endif
