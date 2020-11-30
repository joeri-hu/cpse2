#ifndef ACTION_HPP
#define ACTION_HPP

#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class action {
private:
    std::function<bool()> condition;
    std::function<void()> work;
public:
    action(
        std::function<bool()> condition,
        std::function<void()> work
    );
    action(
        sf::Keyboard::Key key,
        std::function<void()> work
    );
    action(
        drawable const& target,
        std::function<void()> work
    );
    action(std::function<void()> work);
    static void execute(std::vector<action> const& actions);
    void operator()() const;
};

#endif
