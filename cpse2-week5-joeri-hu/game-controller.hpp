#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <map>
#include <vector>

#include "mark.hpp"
#include "move.hpp"
#include "input.hpp"
#include "interface.hpp"
#include "game-logic.hpp"
#include "make-move-cmd.hpp"
#include "exception.hpp"

class game_controller {
public:
    explicit game_controller(interface& user_interface);
    auto run() -> int;
private:
    using pos_table = std::map<input::type, mark::pos>;
    using cmd_list = std::vector<make_move_cmd>;
    interface& user_interface;
    pos_table const positions;
    game_logic game;
    cmd_list commands;
    cmd_list::const_iterator current_cmd;
    mark::type player;
    mark::type first_to_act;

    auto initialize_game() -> void;
    auto reset_game() -> void;
    auto set_acting_player() -> void;
    auto get_pos_table() const -> pos_table;
    auto is_cross_first() const -> bool;
    auto is_nought_first() const -> bool;
    auto is_turn_even() const -> bool;
    auto is_turn_odd() const -> bool;
    auto preceding_cmd_exists() const -> bool;
    auto subsequent_cmd_exists() const -> bool;
    auto toggle_revert_features() const -> void;
    auto process_game_result() -> void;
    auto process_user_input() -> void;
    auto process_move(pos_table::mapped_type pos) -> void;
    auto discard_subsequent_cmds() -> void;
    auto add_command(move new_move) -> void;
    auto undo_command() -> void;
    auto redo_command() -> void;
};

#endif
