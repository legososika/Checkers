#pragma once

#include <SFML/Graphics.hpp>

class UltimatePosition {
 public:
    UltimatePosition(sf::Vector2i pos) {
        _vector_pos = sf::Vector2f(pos.x * 8, pos.y * 8);
        _board_pos = pos;
    }
 private:
    sf::Vector2f _vector_pos;
    sf::Vector2i _board_pos;
};
