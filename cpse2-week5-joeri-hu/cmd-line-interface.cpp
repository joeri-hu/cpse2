#include <string>
#include <iostream>

#include "move.hpp"
#include "mark.hpp"
#include "input.hpp"
#include "utility.hpp"
#include "cmd-line-interface.hpp"

cmd_line_interface::cmd_line_interface():
    markings{get_mark_table()},
    inputs{get_input_table()},
    squares{get_square_table()}
{}

auto cmd_line_interface::get_mark_table() const -> mark_table {
    return {
        {mark::type::cross,  'x'},
        {mark::type::nought, 'o'}
    };
}

auto cmd_line_interface::get_input_table() const -> input_table {
    return {
        {input::type::square1, '1'},
        {input::type::square2, '2'},
        {input::type::square3, '3'},
        {input::type::square4, '4'},
        {input::type::square5, '5'},
        {input::type::square6, '6'},
        {input::type::square7, '7'},
        {input::type::square8, '8'},
        {input::type::square9, '9'},
        {input::type::quit,    'q'}
    };
}

auto cmd_line_interface::get_square_table() const -> square_table {
    return {
        {mark::pos::square1, 1},
        {mark::pos::square2, 3},
        {mark::pos::square3, 5},
        {mark::pos::square4, 15},
        {mark::pos::square5, 17},
        {mark::pos::square6, 19},
        {mark::pos::square7, 29},
        {mark::pos::square8, 31},
        {mark::pos::square9, 33}
    };
}

auto cmd_line_interface::request_mark() -> mark::type {
    std::cout << "\n  who wants to go first?\n\n"
        "  x - crosses\n"
        "  o - noughts\n";
    return request_option(markings);
}

auto cmd_line_interface::request_input() -> input::type {
    std::string options{"\n  1:9 - position\n"};

    if (inputs.count(input::type::undo) not_eq 0) {
        options += "    u - undo move\n";
    }
    if (inputs.count(input::type::redo) not_eq 0) {
        options += "    r - redo move\n";
    }
    std::cout << options << "    q - quit\n";
    return request_option(inputs);
}

template<typename T>
auto cmd_line_interface::request_option(T const& options)
-> typename T::key_type {
    for (auto const prompt = "\n\n> ";;) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        auto const option = util::find_key(options, input[0]);

        if (option not_eq options.cend()) {
            return option->first;
        }
        std::cout << "\n  invalid option :(";
    }
}

auto cmd_line_interface::enable_undo() -> void {
    inputs.try_emplace(input::type::undo, 'u');
}

auto cmd_line_interface::enable_redo() -> void {
    inputs.try_emplace(input::type::redo, 'r');
}

auto cmd_line_interface::disable_undo() -> void {
    inputs.erase(input::type::undo);
}

auto cmd_line_interface::disable_redo() -> void {
    inputs.erase(input::type::redo);
}

auto cmd_line_interface::draw_board(move_table const& moves) const -> void {
    std::string board{
        "\t | | \n"
        "\t-+-+-\n"
        "\t | | \n"
        "\t-+-+-\n"
        "\t | | \n"
    };
    for (auto const [pos, type] : moves) {
        board[squares.at(pos)] = markings.at(type);
    }
    std::cout << board;
}

auto cmd_line_interface::show_banner() const -> void {
    std::cout << 
        "* tic-tac-toe *\n\n"
        "  positions:\n\n"
        "\t1|2|3\n"
        "\t-+-+-\n"
        "\t4|5|6\n"
        "\t-+-+-\n"
        "\t7|8|9\n";
}

auto cmd_line_interface::show_acting_player(mark::type player) -> void {
    std::cout << "\n  " << markings.at(player) << " to move:\n\n";
}

auto cmd_line_interface::show_winning_player(mark::type winner) -> void {
    winner == mark::type::none
        ? std::cout << "\n  it seems to be a draw :/\n\n"
        : std::cout << "\n  player " << markings.at(winner) << " has won! :)\n\n";
}
