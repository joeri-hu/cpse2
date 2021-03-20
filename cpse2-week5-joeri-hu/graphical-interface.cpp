#include <map>
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <sfml/graphics.hpp>

#include "move.hpp"
#include "mark.hpp"
#include "input.hpp"
#include "overload.hpp"
#include "exception.hpp"
#include "utility-sfml.hpp"
#include "graphical-interface.hpp"

inline namespace config {
    namespace window {
        constexpr auto title = "tic-tac-toe";
        constexpr auto fps = 60;
        constexpr auto width = 300;
        constexpr auto height = 400;
        auto const color = sf::Color{25, 25, 25};
        auto const mode = sf::VideoMode{width, height};
        auto const size = sf::Vector2f{width, height};
        auto const rect = sf::FloatRect{{}, size};
        auto const ratio = size / 100.0f;
    }
    using namespace std::string_literals;
}

graphical_interface::graphical_interface():
    window{(load_textures(), window::mode), window::title},
    message{(load_fonts(), ""), font, 20},
    markings{get_mark_table()},
    inputs{get_input_table()},
    squares{get_square_table()},
    board{textures.board}
{
    window.setFramerateLimit(window::fps);
    message.setStyle(sf::Text::Bold);
    message.setFillColor({34, 177, 76});
    message.setPosition(window::ratio * sf::Vector2f{3, 73});
    board.setPosition(window::ratio * sf::Vector2f{4, 0});
}

auto graphical_interface::load_textures() -> void {
    using tx_ref = std::reference_wrapper<sf::Texture>;
    using data = struct {tx_ref contents; std::string file;};
    auto const resources = std::array{
        data{textures.cross,  "resources/cross.png"},
        data{textures.nought, "resources/nought.png"},
        data{textures.none,   "resources/none.png"},
        data{textures.undo,   "resources/undo.png"},
        data{textures.redo,   "resources/redo.png"},
        data{textures.quit,   "resources/quit.png"},
        data{textures.board,  "resources/board.png"}
    };
    std::for_each(resources.cbegin(), resources.cend(),
    [](auto const& texture) -> void {
        if (not texture.contents.get().loadFromFile(texture.file)) {
            throw std::runtime_error(
                "unable to load texture '" + texture.file + "' :(");
        }
    });
}

auto graphical_interface::load_fonts() -> void {
    constexpr auto consola = "resources/consola.ttf";

    if (not font.loadFromFile(consola)) {
        throw std::runtime_error("unable to load font '"s + consola + "' :(");
    }
}

auto graphical_interface::get_mark_table() const -> mark_table {
    mark_table markings;
    markings.emplace(mark::type::cross, textures.cross).first->second
        .setPosition(window::ratio * sf::Vector2f{24, 83});
    markings.emplace(mark::type::nought, textures.nought).first->second
        .setPosition(window::ratio * sf::Vector2f{58, 83});
    return markings;
}

auto graphical_interface::get_input_table() const -> input_table {
    input_table inputs;
    inputs.emplace(input::type::square1, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{8, 7});
    inputs.emplace(input::type::square2, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{41, 7});
    inputs.emplace(input::type::square3, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{74, 7});
    inputs.emplace(input::type::square4, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{8, 31});
    inputs.emplace(input::type::square5, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{41, 31});
    inputs.emplace(input::type::square6, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{74, 31});
    inputs.emplace(input::type::square7, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{8, 54});
    inputs.emplace(input::type::square8, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{41, 54});
    inputs.emplace(input::type::square9, textures.none).first->second
        .setPosition(window::ratio * sf::Vector2f{74, 54});
    inputs.emplace(input::type::quit, textures.quit).first->second
        .setPosition(window::ratio * sf::Vector2f{71, 81});
    return inputs;
}

auto graphical_interface::get_square_table() -> square_table {
    return {
        {mark::pos::square1, inputs.at(input::type::square1)},
        {mark::pos::square2, inputs.at(input::type::square2)},
        {mark::pos::square3, inputs.at(input::type::square3)},
        {mark::pos::square4, inputs.at(input::type::square4)},
        {mark::pos::square5, inputs.at(input::type::square5)},
        {mark::pos::square6, inputs.at(input::type::square6)},
        {mark::pos::square7, inputs.at(input::type::square7)},
        {mark::pos::square8, inputs.at(input::type::square8)},
        {mark::pos::square9, inputs.at(input::type::square9)}
    };
}

auto graphical_interface::request_mark() -> mark::type {
    message.setString("who wants to go first?");
    return request_option(markings);
}

auto graphical_interface::request_input() -> input::type {
    return request_option(inputs);
}

template<typename T>
auto graphical_interface::request_option(T const& options)
-> typename T::key_type {
    while (window.isOpen()) {
        if (window.hasFocus() and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto const mouse_pos = util::get_mouse_pos(window);

            if (window::rect.contains(mouse_pos)) {
                auto const option = util::find_target(options, mouse_pos);

                if (option not_eq options.cend()) {
                    sf::sleep(sf::milliseconds(200));
                    return option->first;
                }
            }
        }
        process_events();
        draw(options);
    }
    throw exit_program();
}

auto graphical_interface::process_events() -> void {
    for (sf::Event event; window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
            return window.close();
        }
    }
}

template<typename T>
auto graphical_interface::draw(T const& options) -> void {
    window.clear(window::color);
    window.draw(board);
    window.draw(message);
    std::for_each(options.cbegin(), options.cend(),
    [this](auto const& option) -> void {
        window.draw(option.second);
    });
    window.display();
}

auto graphical_interface::enable_undo() -> void {
    inputs.try_emplace(input::type::undo, textures.undo).first->second
        .setPosition(window::ratio * sf::Vector2f{3, 81});
}

auto graphical_interface::enable_redo() -> void {
    inputs.try_emplace(input::type::redo, textures.redo).first->second
        .setPosition(window::ratio * sf::Vector2f{32, 81});
}

auto graphical_interface::disable_undo() -> void {
    inputs.erase(input::type::undo);
}

auto graphical_interface::disable_redo() -> void {
    inputs.erase(input::type::redo);
}

auto graphical_interface::draw_board(move_table const& moves) const -> void {
    for (auto const& [pos, square] : squares) {
        auto const move = moves.find(pos);
        square.get().setTexture(move == moves.cend()
            ? textures.none
            : *markings.at(move.get_type()).getTexture());
    }
}

auto graphical_interface::show_banner() const -> void {}

auto graphical_interface::show_acting_player(mark::type player) -> void {
    message.setString(get_mark_symbol(player) + " to move"s);
}

auto graphical_interface::show_winning_player(mark::type winner, int delay_s) -> void {
    message.setString(winner == mark::type::none
        ? "it seems to be a draw :/"
        : "player "s + get_mark_symbol(winner) + " has won! :)");
    draw(inputs);
    sf::sleep(sf::seconds(delay_s));
}

auto graphical_interface::get_mark_symbol(mark::type type) const -> char {
    return type == mark::type::cross ? 'x' : 'o';
}
