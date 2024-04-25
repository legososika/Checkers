#pragma once

#include <SFML/Graphics.hpp>
#include "Checker.h"

class Dummy {
 public:
    explicit Dummy(sf::Vector2f pos) {
        _activated = false;
        _to_kill = false;
        _target = {0, 0};
        _sprite.setRadius(40);
        _sprite.setFillColor(sf::Color(50, 50, 50));
        _sprite.setPosition(pos);
    }
    bool contains(sf::Vector2f pos) const {
        return _sprite.getGlobalBounds().contains(pos);
    }
    void setActivation(bool activated) {
        _activated = activated;
    }
    bool isActivated() const {
        return _activated;
    }
    sf::Vector2f getPos() const {
        return _sprite.getPosition();
    }
    void setKill(bool to_kill) {
        _to_kill = to_kill;
    }
    bool isToKill() const {
        return _to_kill;
    }
    void draw(sf::RenderWindow& window)  {
        window.draw(_sprite);
    }
    void setTarget(sf::Vector2i target) {
        _target = target;
    }
    sf::Vector2i getTarget() const {
        return _target;
    }
 private:
    bool _activated;
    bool _to_kill;
    sf::CircleShape _sprite;
    sf::Vector2i _target;
};
