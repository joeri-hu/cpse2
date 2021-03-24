#ifndef GRAPHICAL_INTERFACE_HPP
#define GRAPHICAL_INTERFACE_HPP

#include <map>
#include <functional>
#include <sfml/graphics.hpp>

#include "move.hpp"
#include "mark.hpp"
#include "input.hpp"
#include "interface.hpp"

class graphical_interface : public interface {
public:
    graphical_interface();
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
    using mark_table = std::map<mark::type, sf::Sprite>;
    using input_table = std::map<input::type, sf::Sprite>;
    using sprite_ref = std::reference_wrapper<sf::Sprite>;
    using square_table = std::map<mark::pos, sprite_ref>;
    struct {
        sf::Texture cross;
        sf::Texture nought;
        sf::Texture none;
        sf::Texture undo;
        sf::Texture redo;
        sf::Texture quit;
        sf::Texture board;
    } textures;
    sf::Font font;
    sf::RenderWindow window;
    sf::Text message;
    mark_table const markings;
    input_table inputs;
    square_table const squares;
    sf::Sprite board;

    auto load_textures() -> void;
    auto load_fonts() -> void;
    auto get_mark_table() const -> mark_table;
    auto get_input_table() const -> input_table;
    auto get_square_table() -> square_table;
    template<typename T>
    auto request_option(T const& options) -> typename T::key_type;
    auto process_events() -> void;
    template<typename T>
    auto draw(T const& options) -> void;
    auto get_mark_symbol(mark::type type) const -> char;
};

#endif
