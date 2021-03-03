#ifndef PLACEABLE_HPP
#define PLACEABLE_HPP

#include <ostream>
#include <sfml/graphics.hpp>

class placeable : public sf::Drawable {
public:
    virtual ~placeable() = default;
    placeable(placeable const&) = delete;
    placeable& operator=(placeable const&) = delete;
    placeable(placeable&&) = delete;
    placeable& operator=(placeable&&) = delete;

    virtual auto contains(sf::Vector2f const& target) const noexcept -> bool = 0;
    virtual auto set_center_pos(sf::Vector2f const& position) noexcept -> void = 0;
    virtual auto to_string(std::ostream& output) const -> std::ostream& = 0;
protected:
    explicit placeable(sf::Drawable const& drawable) noexcept;
    placeable(sf::Drawable const& drawable, sf::Vector2f const& center) noexcept;
    sf::Vector2f center;
private:
    sf::Drawable const& drawable;
    auto draw(
        sf::RenderTarget& window,
        sf::RenderStates states
    ) const noexcept -> void override;
};

auto operator<<(std::ostream& output, placeable const& input) -> std::ostream&;

#endif
