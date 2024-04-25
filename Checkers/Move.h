#pragma once

#include <SFML/Graphics.hpp>

struct Move {
    sf::Vector2i pos_end, pos_start;
    bool kill;
    sf::Vector2i target;
    bool side = false;
    Move() {
        pos_end = {-1, -1}, pos_start = {-1, -1};
        kill = false;
        target = {-1, -1};
    }
    Move(sf::Vector2i pos_, bool kill_, sf::Vector2i target_, sf::Vector2i pos_start_ = {0, 0}) : pos_end(pos_),
    kill(kill_), target(target_), pos_start(pos_start_) { };
};
