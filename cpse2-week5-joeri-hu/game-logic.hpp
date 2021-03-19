#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <map>
#include <array>
#include <vector>
#include <optional>

#include "mark.hpp"
#include "move.hpp"

class game_logic {
private:
    static constexpr auto seq_size = 3;
    using seq_list = std::array<mark::pos, seq_size>;
    using seq_table = std::map<mark::pos, std::vector<seq_list>>;
    seq_table const winning_seqs;
    seq_table::size_type const board_size;
    move_table moves;
    move_table::const_iterator last_move;
public:
    game_logic();
    auto get_sequence_table() const -> seq_table;
    auto get_winning_player() const -> mark::type;
    auto sequence_matches(seq_list const& sequence) const -> bool;
    auto get_moves() const -> move_table const&;
    auto get_move_count() const -> move_table::size_type;
    auto move_exists(move_table::key_type pos) const -> bool;
    auto is_board_full() const -> bool;
    auto add_move(move_table::value_type const& move) -> void;
    auto add_move(move_table::value_type&& move) -> void;
    auto delete_move(move_table::key_type pos) -> void;
    auto reset_moves() -> void;
};

#endif
