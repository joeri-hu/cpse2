#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "action.hpp"
#include "drawable.hpp"
#include "ball.hpp"
#include "box.hpp"
#include "wall.hpp"

void addSuperballInteraction(
    std::vector<action>& actions,
    ball& superball,
    float const& speed
) {
    actions.push_back({[&]{superball.update({speed, 0});}});
    actions.push_back({superball, [&]{
        superball.bounce({-1, 1});
        superball.update({speed, 0});}}
    );
    actions.push_back({[&]{superball.update({0, speed});}});
    actions.push_back({superball, [&]{
        superball.bounce({1, -1});
        superball.update({0, speed});}});
}

int main(int argc, char *argv[]) {
    constexpr auto width = 640;
    constexpr auto height = 480;
    sf::RenderWindow window{
        sf::VideoMode{width, height},
        "SFML window"
    };
    constexpr auto size = 20;
    wall const boundaries[]{
        {{0, 0}, {width, size}},
        {{0, height - size}, {width, size}},
        {{0, size}, {size, height - size * 2}},
        {{width - size, size}, {size, height - size * 2}}
    };
    box player{{width / 4, height / 4}, {50, 50}, sf::Color::Blue};
    static constexpr float speed{1};
    struct {
        sf::Vector2f left{-speed, 0};
        sf::Vector2f right{+speed, 0};
        sf::Vector2f up{0, -speed};
        sf::Vector2f down{0, +speed};
    } direction;
    action const& invertMoveOnOverlap{player, [&]{player.invertMove();}};
    std::vector<action> actions{
        {sf::Keyboard::Escape, [&]{window.close();}},
        {sf::Keyboard::Up,
            [&]{player.move(direction.up); invertMoveOnOverlap();}},
        {sf::Keyboard::Down,
            [&]{player.move(direction.down); invertMoveOnOverlap();}},
        {sf::Keyboard::Left,
            [&]{player.move(direction.left); invertMoveOnOverlap();}},
        {sf::Keyboard::Right,
            [&]{player.move(direction.right); invertMoveOnOverlap();}},
    };
    ball superball1{{width / 2, height / 2}, 30, sf::Color::Red};
    // ball superball2{{width / 3, height / 3}, 30, sf::Color::Yellow};
    // ball superball3{{width / 2, height / 4}, 30, sf::Color::Cyan};
    // ball superball4{{width / 7, height / 5}, 30, sf::Color::Magenta};
    addSuperballInteraction(actions, superball1, speed);
    // addSuperballMovement(actions, superball2, speed);
    // addSuperballMovement(actions, superball3, speed);
    // addSuperballMovement(actions, superball4, speed);

    while (window.isOpen()) {
        action::execute(actions);
        window.clear();
        drawable::drawAll(window);
        window.display();
        sf::sleep(sf::milliseconds(7));
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    return 0;
}
