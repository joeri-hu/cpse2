#ifndef MAKE_MOVE_CMD_HPP
#define MAKE_MOVE_CMD_HPP

#include "move.hpp"
#include "command.hpp"
#include "game-logic.hpp"

class make_move_cmd : public command {
public:
    explicit make_move_cmd(move new_move);
    auto execute(game_logic& game) const -> void override;
    auto undo(game_logic& game) const -> void override;
private:
    move new_move;
};

#endif
