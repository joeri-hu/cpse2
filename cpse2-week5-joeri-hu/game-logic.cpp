#include <map>
#include <array>
#include <vector>
#include <optional>
#include <algorithm>

#include "mark.hpp"
#include "move.hpp"
#include "game-logic.hpp"

game_logic::game_logic():
    winning_seqs{get_sequence_table()},
    board_size{winning_seqs.size()}
{}

auto game_logic::get_sequence_table() const -> seq_table {
    using namespace mark;
    constexpr auto hor_top   = seq_list{pos::square1, pos::square2, pos::square3};
    constexpr auto hor_mid   = seq_list{pos::square4, pos::square5, pos::square6};
    constexpr auto hor_down  = seq_list{pos::square7, pos::square8, pos::square9};
    constexpr auto ver_left  = seq_list{pos::square1, pos::square4, pos::square7};
    constexpr auto ver_mid   = seq_list{pos::square2, pos::square5, pos::square8};
    constexpr auto ver_right = seq_list{pos::square3, pos::square6, pos::square9};
    constexpr auto diag_desc = seq_list{pos::square1, pos::square5, pos::square9};
    constexpr auto diag_asc  = seq_list{pos::square7, pos::square5, pos::square3};
    return {
        {pos::square1, {hor_top,  ver_left,  diag_desc}},
        {pos::square2, {hor_top,  ver_mid}},
        {pos::square3, {hor_top,  ver_right, diag_asc}},
        {pos::square4, {hor_mid,  ver_left}},
        {pos::square5, {hor_mid,  ver_mid,   diag_asc, diag_desc}},
        {pos::square6, {hor_mid,  ver_right}},
        {pos::square7, {hor_down, ver_left,  diag_asc}},
        {pos::square8, {hor_down, ver_mid}},
        {pos::square9, {hor_down, ver_right, diag_desc}}
    };
}

auto game_logic::get_winning_player() const -> mark::type {
    if (get_move_count() >= 5) {
        for (auto const& sequence : winning_seqs.at(last_move.get_pos())) {
            if (sequence_matches(sequence)) {
                return last_move.get_type();
            }
        }
    }
    return mark::type::none;
}

auto game_logic::sequence_matches(seq_list const& sequence) const -> bool {
    return std::all_of(sequence.cbegin(), sequence.cend(),
    [this](auto const& pos) -> bool {
        auto const move = moves.find(pos);
        return move not_eq moves.cend()
            and move.get_type() == last_move.get_type();
    });
}

auto game_logic::get_moves() const -> move_table const& {
    return moves;
}

auto game_logic::get_move_count() const -> move_table::size_type {
    return moves.size();
}

auto game_logic::move_exists(move_table::key_type pos) const -> bool {
    return moves.count(pos) not_eq 0;
}

auto game_logic::is_board_full() const -> bool {
    return moves.size() == board_size;
}

auto game_logic::add_move(move_table::value_type const& move) -> void {
    last_move = moves.insert(move);
}

auto game_logic::add_move(move_table::value_type&& move) -> void {
    last_move = moves.insert(std::move(move));
}

auto game_logic::delete_move(move_table::key_type pos) -> void {
    moves.erase(pos);
}

auto game_logic::reset_moves() -> void {
    moves.clear();
}
