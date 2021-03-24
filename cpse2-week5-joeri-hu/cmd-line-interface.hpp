#ifndef CMD_LINE_INTERFACE_HPP
#define CMD_LINE_INTERFACE_HPP

#include <map>
#include "move.hpp"
#include "mark.hpp"
#include "input.hpp"
#include "interface.hpp"

class cmd_line_interface : public interface {
public:
    cmd_line_interface();
    auto enable_undo() -> void override;
    auto enable_redo() -> void override;
    auto disable_undo() -> void override;
    auto disable_redo() -> void override;
    auto request_mark() -> mark::type override;
    auto request_input() -> input::type override;
    auto draw_board(move_table const& moves) const -> void override;
    auto show_banner() const -> void override;
    auto show_acting_player(mark::type player) -> void override;
    auto show_winning_player(mark::type winner) -> void override;
private:
    using mark_table = std::map<mark::type, char>;
    using input_table = std::map<input::type, char>;
    using square_table = std::map<mark::pos, int8_t>;
    mark_table const markings;
    input_table inputs;
    square_table const squares;

    auto get_mark_table() const -> mark_table;
    auto get_square_table() const -> square_table;
    auto get_input_table() const -> input_table;
    template<typename T>
    auto request_option(T const& options) -> typename T::key_type;
};

#endif
