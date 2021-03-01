#ifndef PLACEABLE_FACTORY_HPP
#define PLACEABLE_FACTORY_HPP

#include <tuple>
#include <string>
#include <fstream>
#include <experimental/memory>
#include <sfml/graphics.hpp>

#include "experimental.hpp"
#include "placeable.hpp"
#include "placeable-handler.hpp"

class placeable_factory {
public:
    placeable_factory(placeable_handler& handler, std::string resource_file) noexcept;
    ~placeable_factory();
    placeable_factory(placeable_factory const&) = delete;
    placeable_factory& operator=(placeable_factory const&) = delete;
    placeable_factory(placeable_factory&&) = delete;
    placeable_factory& operator=(placeable_factory&&) = delete;

    auto import_resources() noexcept -> void;
    auto export_resources() noexcept -> void;
protected:
    template<typename... Ts>
    static auto read_values(std::ifstream& input) -> std::tuple<Ts...>;
    template<typename P, typename... Ts>
    static auto parse(
        std::ifstream& input,
        sf::Vector2f const& start,
        Ts&&... args
    ) -> ste::observer_ptr<P>;
private:
    placeable_handler& handler;
    std::string resource_file;
    bool is_import_valid;
    auto process_resource(std::ifstream& input) -> ste::observer_ptr<placeable>;
};

template<typename T>
std::ifstream& operator>>(std::ifstream& input, sf::Vector2<T>& output);
std::ifstream& operator>>(std::ifstream& input, sf::Color& output);

#endif
