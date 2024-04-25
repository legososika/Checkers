#pragma once

#include <SFML/Graphics.hpp>

//#include "UltimatePosition.h"

class Checker {
 public:
    Checker(sf::Vector2f pos, int side, sf::Color color) :
    _pos(pos), _side(side), _color(color)  {
        _sprite.setRadius(40);
        _sprite.setFillColor(color);
        _sprite.setPosition(_pos);
    }
    int getSide() const {
        return _side;
    }
    bool isQueen() const {
        return _queen;
    }
    void becomeQueen() {
        _queen = true;
        _sprite.setOutlineColor(sf::Color::Red);
        _sprite.setOutlineThickness(7);
    }
    void becomeFakeQueen() {
        _fake_queen = true;
    }
    bool isFakeQueen() const {
        return _fake_queen;
    }
    void draw(sf::RenderWindow& window) {
        window.draw(_sprite);
    }
    bool contains(sf::Vector2f pos) {
        return _sprite.getGlobalBounds().contains(pos);
    }
    sf::CircleShape getSprite() const {
        return _sprite;
    }
    void changePos(sf::Vector2f pos) {
        _pos = pos;
        _sprite.setPosition(_pos);
    }
    void changePos(float x, float y = 0) {
        _pos.x += x;
        _pos.y += y;
        _sprite.setPosition(_pos);
    }
    void setColor(sf::Color col) {
        _color = col;
        _sprite.setFillColor(_color);
    }
    void setArrPos(sf::Vector2i pos) {
        _arr_pos = pos;
    }
    sf::Vector2i getArrPos() const {
        return _arr_pos;
    }
 private:
    sf::Vector2f _pos;
    int _side;
    sf::Color _color;
    sf::CircleShape _sprite;
    bool _queen = false;
    bool _fake_queen = false;
    sf::Vector2i _arr_pos;
};


