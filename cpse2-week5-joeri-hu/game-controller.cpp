#include <vector>
#include <cstdlib>
#include <iostream>
#include <exception>

#include "mark.hpp"
#include "move.hpp"
#include "input.hpp"
#include "exception.hpp"
#include "interface.hpp"
#include "game-logic.hpp"
#include "make-move-cmd.hpp"
#include "game-controller.hpp"

game_controller::game_controller(interface& user_interface):
    user_interface{user_interface},
    positions{get_pos_table()}
{}

auto game_controller::get_pos_table() const -> pos_table {
    return {
        {input::type::square1, mark::pos::square1},
        {input::type::square2, mark::pos::square2},
        {input::type::square3, mark::pos::square3},
        {input::type::square4, mark::pos::square4},
        {input::type::square5, mark::pos::square5},
        {input::type::square6, mark::pos::square6},
        {input::type::square7, mark::pos::square7},
        {input::type::square8, mark::pos::square8},
        {input::type::square9, mark::pos::square9}
    };
}

auto game_controller::run() -> int {
    try {
        for (initialize_game();;) {
            set_acting_player();
            user_interface.show_acting_player(player);
            user_interface.draw_board(game.get_moves());
            toggle_revert_features();
            process_user_input();
            process_game_result();
        }
    } catch (exit_program const& exc) {
        return EXIT_SUCCESS;
    } catch (std::exception const& exc) {
        std::cerr << "unexpected error occured: "
            << exc.what() << " :(" << std::endl;
    }
    return EXIT_FAILURE;
}

auto game_controller::initialize_game() -> void {
    user_interface.show_banner();
    first_to_act = user_interface.request_mark();
}

auto game_controller::set_acting_player() -> void {
    player = (is_cross_first() and is_turn_even())
        or (is_nought_first() and is_turn_odd())
            ? mark::type::cross
            : mark::type::nought;
}

auto game_controller::is_cross_first() const -> bool {
    return first_to_act == mark::type::cross;
}

auto game_controller::is_nought_first() const -> bool {
    return first_to_act == mark::type::nought;
}

auto game_controller::is_turn_even() const -> bool {
    return not is_turn_odd();
}

auto game_controller::is_turn_odd() const -> bool {
    return game.get_move_count() bitand 1;
}

auto game_controller::toggle_revert_features() const -> void {
    preceding_cmd_exists()
        ? user_interface.enable_undo()
        : user_interface.disable_undo();
    subsequent_cmd_exists()
        ? user_interface.enable_redo()
        : user_interface.disable_redo();
}

auto game_controller::preceding_cmd_exists() const -> bool {
    return current_cmd not_eq commands.cbegin();
}

auto game_controller::subsequent_cmd_exists() const -> bool {
    return current_cmd not_eq commands.cend();
}

auto game_controller::process_user_input() -> void {
    switch (auto const input = user_interface.request_input(); input) {
    case input::type::undo: undo_command(); break;
    case input::type::redo: redo_command(); break;
    case input::type::quit: throw exit_program(); break;
    default: process_move(positions.at(input)); break;
    }
}

auto game_controller::undo_command() -> void {
    --current_cmd;
    current_cmd->undo(game);
}

auto game_controller::redo_command() -> void {
    current_cmd->execute(game);
    ++current_cmd;
}

auto game_controller::process_move(pos_table::mapped_type pos) -> void {
    if (game.move_exists(pos)) {
        return;
    }
    discard_subsequent_cmds();
    add_command({{pos, player}});
    commands.back().execute(game);
}

auto game_controller::discard_subsequent_cmds() -> void {
    if (subsequent_cmd_exists()) {
        commands.erase(current_cmd, commands.cend());
    }
}

auto game_controller::add_command(move new_move) -> void {
    commands.emplace_back(std::move(new_move));
    current_cmd = commands.cend();
}

auto game_controller::process_game_result() -> void {
    if (subsequent_cmd_exists()) {
        return;
    }
    auto const winner = game.get_winning_player();

    if (winner not_eq mark::type::none or game.is_board_full()) {
        user_interface.draw_board(game.get_moves());
        user_interface.show_winning_player(winner);
        reset_game();
    }
}

auto game_controller::reset_game() -> void {
    commands.clear();
    current_cmd = commands.cend();
    game.reset_moves();
    user_interface.disable_undo();
    user_interface.disable_redo();
    initialize_game();
}
