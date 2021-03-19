#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "move.hpp"
#include "mark.hpp"
#include "input.hpp"

class interface {
public:
    interface(interface const&) = delete;
    interface& operator=(interface const&) = delete;
    interface(interface&&) = delete;
    interface& operator=(interface&&) = delete;

    virtual auto enable_undo() -> void = 0;
    virtual auto enable_redo() -> void = 0;
    virtual auto disable_undo() -> void = 0;
    virtual auto disable_redo() -> void = 0;
    virtual auto request_mark() -> mark::type = 0;
    virtual auto request_input() -> input::type = 0;
    virtual auto draw_board(move_table const& moves) const -> void = 0;
    virtual auto show_banner() const -> void = 0;
    virtual auto show_acting_player(mark::type player) -> void = 0;
    virtual auto show_winning_player(mark::type winner, int delay_s = 4) -> void = 0;
protected:
    interface() = default;
    ~interface() = default;
};

#endif
