#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "action.hpp"

action::action(
    std::function<bool()> condition,
    std::function<void()> work
):
    condition{condition},
    work{work} 
{}

action::action(
    sf::Keyboard::Key key,
    std::function<void()> work
):
    action(
        [=]{return sf::Keyboard::isKeyPressed(key);},
        work
    )
{}

action::action(
    drawable const& target,
    std::function<void()> work
):
    action([&]{return drawable::anyObjectOverlaps(target);}, work)
{}

action::action(std::function<void()> work):
    action([]{return true;}, work)
{}

void action::execute(std::vector<action> const& actions) {
    for (auto const& action : actions) {
        action();
    }
}

void action::operator()() const {
    if (condition()){
        work();
    }
}
