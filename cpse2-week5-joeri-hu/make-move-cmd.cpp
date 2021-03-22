#include "move.hpp"
#include "game-logic.hpp"
#include "make-move-cmd.hpp"

make_move_cmd::make_move_cmd(move new_move):
    current_move{std::move(new_move)}
{}

auto make_move_cmd::execute(game_logic& game) const -> void {
    game.add_move(current_move);
}

auto make_move_cmd::undo(game_logic& game) const -> void {
    game.delete_move(current_move.get_pos());
}
