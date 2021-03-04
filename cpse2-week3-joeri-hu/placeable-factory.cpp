#include <array>
#include <tuple>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <functional>
#include <experimental/memory>
#include <sfml/graphics.hpp>

#include "experimental.hpp"
#include "exceptions.hpp"
#include "utilities.hpp"
#include "placeable.hpp"
#include "line.hpp"
#include "rect.hpp"
#include "circle.hpp"
#include "picture.hpp"
#include "placeable-handler.hpp"
#include "placeable-factory.hpp"

placeable_factory::placeable_factory(
    placeable_handler& handler,
    std::string resource_file
) noexcept:
    handler{handler},
    resource_file{resource_file},
    is_import_valid{false}
{}

placeable_factory::~placeable_factory() {
    if (is_import_valid) {
        export_resources();
    }
}

auto placeable_factory::export_resources() noexcept -> void {
    std::ofstream output{resource_file};
    handler.print_all(output);
}

auto placeable_factory::import_resources() noexcept -> void {
    try {
        std::ifstream input{resource_file};
        for (;;) {
            handler.add(process_resource(input));
        }
    } catch (end_of_file const& exc) {
        is_import_valid = true;
        return;
    } catch (std::exception const& exc) {
        std::cerr << exc.what() << std::endl;
        is_import_valid = false;
    }
}

auto placeable_factory::process_resource(
    std::ifstream& input
) -> ste::observer_ptr<placeable> {
    auto const [start, name] = parse(input, sf::Vector2f(), std::string());
    using func = std::function<ste::observer_ptr<placeable>()>;
    using data = struct {std::string_view name; func action;};

    auto const options = std::array{
        data{"line", [&]{return make<line>(input, start, sf::Vector2f(), sf::Color());}},
        data{"circle", [&]{return make<circle>(input, start, sf::Color(), float());}},
        data{"rect", [&]{return make<rect>(input, start, sf::Vector2f(), sf::Color());}},
        data{"picture", [&]{return make<picture>(input, start, std::string());}},
        data{"", []{throw end_of_file(); return nullptr;}}
    };
    for (auto const& option : options) {
        if (option.name == name) {
            return option.action();
        }
    }
    throw unknown_shape(name);
}

template<typename... Ts>
auto placeable_factory::parse(std::ifstream& input, Ts&&... args) -> std::tuple<Ts...> {
    (input >> ... >> args);
    return {std::forward<Ts>(args)...};
}

template<typename P, typename... Ts>
auto placeable_factory::make(
    std::ifstream& input,
    sf::Vector2f const& start,
    Ts&&... args
) -> ste::observer_ptr<P> {
    (input >> ... >> args);
    return ste::make_observer<P>(start, std::forward<Ts>(args)...);
}

template<typename T>
auto operator>>(std::ifstream& input, sf::Vector2<T>& output) -> std::ifstream& {
    char symbol;
    if (not (input >> symbol))   {throw end_of_file();}
    if (symbol not_eq '(')       {throw invalid_position(symbol);}
    if (not (input >> output.x)) {throw invalid_position();}
    if (not (input >> symbol))   {throw unexpected_end_of_file();}
    if (symbol not_eq ',')       {throw invalid_position(symbol);}
    if (not (input >> output.y)) {throw invalid_position();}
    if (not (input >> symbol))   {throw unexpected_end_of_file();}
    if (symbol not_eq ')')       {throw invalid_position(symbol);}
    return input;
}

auto operator>>(std::ifstream& input, sf::Color& output) -> std::ifstream& {
    std::string name;
    input >> name;

    for (auto const& option : util::get_color_table()) {
        if (option.name == name) {
            output = option.color;
            return input;
        }
    }
    if (name == "") {
        throw end_of_file();
    }
    throw unknown_color(name);
}
