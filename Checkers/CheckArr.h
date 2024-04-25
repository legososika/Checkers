#pragma once

#include "Checker.h"
#include "Move.h"
#include "Dummy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class CheckArr {
 public:
    explicit CheckArr(sf::Color black_piece_color, sf::Color white_piece_color) :
    _black_piece_color(black_piece_color), _white_piece_color(white_piece_color) {
        _checkers.resize(8, std::vector<Checker*>(8, nullptr));
    }

    Checker* getChecker(sf::Vector2i pos) {
        return _checkers[pos.x][pos.y];
    }

    bool isTimeToKill() const {
        return _killing_time;
    }

    void setup(int x_ch = 615, int y_ch = 260) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0 + 1 - i % 2; j < 8; j += 2) {
                _checkers[i][j] = new Checker({float(0 + j * 128 + x_ch), float(0 + i * 128 + y_ch)},
                                             0, _black_piece_color);
            }
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0 + i % 2; j < 8; j += 2) {
                _checkers[7 - i][j] = new Checker({float(0 + j * 128 + x_ch), float(0 + (7 - i) * 128 + y_ch)},
                                                 1, _white_piece_color);
            }
        }
    }

    void reset() {
        for (int i = 0; i < _checkers.size(); ++i) {
            for (int j = 0; j < _checkers[i].size(); ++j) {
                if (_checkers[i][j]) {
                    Checker* to_delete = _checkers[i][j];
                    _checkers[i][j] = nullptr;
                    delete to_delete;
                }
            }
        }
        _killing_time = false;
        setup();
    }

    std::vector<Move> getMovesForOne(sf::Vector2i pos, bool practice = false, bool kill_check = false, bool personal_check = false) {
        if (kill_check) {
            _killing_time = false;
            _possible_moves.clear();
        }
        if (personal_check) {
            _possible_moves.clear();
        }
        if (_checkers[pos.x][pos.y] == nullptr) {
            std::cout << "HOW HOW HOW HOW HOW\n";
            return _possible_moves;
        }
        if (_checkers[pos.x][pos.y]->isQueen() /*|| practice && _checkers[pos.x][pos.y]->isFakeQueen()*/) {
            std::vector<Move> top_left, top_right, bot_left, bot_right;
            int x = pos.x - 1;
            int y = pos.y - 1;
            while (x >= 0 && y >= 0) {
                if (_checkers[x][y] != nullptr && _checkers[x][y]->getSide() == _checkers[pos.x][pos.y]->getSide()) {
                    break;
                }
                if (_checkers[x][y] != nullptr && _checkers[x][y]->getSide() != _checkers[pos.x][pos.y]->getSide()) {
                    if (x - 1 >= 0 && y - 1 >= 0 && _checkers[x - 1][y - 1] == nullptr) {
                        if (!_killing_time) {
                            top_left.clear();
                            _possible_moves.clear();
                        }

                        top_left.push_back(Move({x - 1, y - 1}, true,
                                                {x, y}, pos));
                        _killing_time = true;
                    }
                    break;
                }
                if (_checkers[x][y] == nullptr && !_killing_time) {
                    top_left.push_back(Move({x, y}, false, {0, 0}, pos));
                }
                --x;
                --y;
            }
            x = pos.x - 1;
            y = pos.y + 1;
            while (x >= 0 && y < 8) {
                if (_checkers[x][y] != nullptr && _checkers[x][y]->getSide() == _checkers[pos.x][pos.y]->getSide()) {
                    break;
                }
                if (_checkers[x][y] != nullptr && _checkers[x][y]->getSide() != _checkers[pos.x][pos.y]->getSide()) {
                    if (x - 1 >= 0 && y + 1 < 8 && _checkers[x - 1][y + 1] == nullptr) {
                        if (!_killing_time) {
                            top_left.clear();
                            top_right.clear();
                            _possible_moves.clear();
                        }
                        top_right.push_back(Move({x - 1, y + 1}, true,
                                                {x, y}, pos));
                        _killing_time = true;
                    }
                    break;
                }
                if (_checkers[x][y] == nullptr && !_killing_time) {
                    top_right.push_back(Move({x, y}, false, {0, 0}, pos));
                }
                --x;
                ++y;
            }
            x = pos.x + 1;
            y = pos.y + 1;
            while (x < 8 && y < 8) {
                if (_checkers[x][y] != nullptr && _checkers[x][y]->getSide() == _checkers[pos.x][pos.y]->getSide()) {
                    break;
                }
                if (_checkers[x][y] != nullptr && _checkers[x][y]->getSide() != _checkers[pos.x][pos.y]->getSide()) {
                    if (x + 1 < 8 && y + 1 < 8 && _checkers[x + 1][y + 1] == nullptr) {
                        if (!_killing_time) {
                            top_left.clear();
                            top_right.clear();
                            bot_right.clear();
                            _possible_moves.clear();
                        }
                        bot_right.push_back(Move({x + 1, y + 1}, true,
                                                {x, y}, pos));
                        _killing_time = true;
                    }
                    break;
                }
                if (_checkers[x][y] == nullptr && !_killing_time) {
                    bot_right.push_back(Move({x, y}, false, {0, 0}, pos));
                }
                ++y;
                ++x;
            }
            x = pos.x + 1;
            y = pos.y - 1;
            while (x < 8 && y >= 0) {
                if (_checkers[x][y] != nullptr && _checkers[x][y]->getSide() == _checkers[pos.x][pos.y]->getSide()) {
                    break;
                }
                if (_checkers[x][y] != nullptr && _checkers[x][y]->getSide() != _checkers[pos.x][pos.y]->getSide()) {
                    if (x + 1 < 8 && y - 1 >= 0 && _checkers[x + 1][y - 1] == nullptr) {
                        if (!_killing_time) {
                            top_left.clear();
                            top_right.clear();
                            bot_right.clear();
                            bot_left.clear();
                            _possible_moves.clear();
                        }
                        bot_left.push_back(Move({x + 1, y - 1}, true,
                                                {x, y}, pos));
                        _killing_time = true;
                    }
                    break;
                }
                if (_checkers[x][y] == nullptr && !_killing_time) {
                    bot_left.push_back(Move({x, y}, false, {0, 0}, pos));
                }
                --y;
                ++x;
            }
            _possible_moves.insert(_possible_moves.end(), top_left.begin(), top_left.end());
            _possible_moves.insert(_possible_moves.end(), top_right.begin(), top_right.end());
            _possible_moves.insert(_possible_moves.end(), bot_left.begin(), bot_left.end());
            _possible_moves.insert(_possible_moves.end(), bot_right.begin(), bot_right.end());
            return _possible_moves;
        }

        if (pos.x - 1 >= 0 && pos.y - 1 >= 0) {
            if (_checkers[pos.x - 1][pos.y - 1] != nullptr &&
                _checkers[pos.x - 1][pos.y - 1]->getSide() != _checkers[pos.x][pos.y]->getSide()) {
                if (pos.x - 2 >= 0 && pos.y - 2 >= 0 && _checkers[pos.x - 2][pos.y - 2] == nullptr) {
                    if (!_killing_time) {
                        _possible_moves.clear();
                    }
                    _possible_moves.push_back(Move({pos.x - 2, pos.y - 2}, true,
                                         {pos.x - 1, pos.y - 1}, pos));
                    _killing_time = true;
                }
            }
        }
        if (pos.x + 1 < 8 && pos.y - 1 >= 0) {
            if (_checkers[pos.x + 1][pos.y - 1] != nullptr &&
                _checkers[pos.x + 1][pos.y - 1]->getSide() != _checkers[pos.x][pos.y]->getSide()) {
                if (pos.x + 2 < 8 && pos.y - 2 >= 0 && _checkers[pos.x + 2][pos.y - 2] == nullptr) {
                    if (!_killing_time) {
                        _possible_moves.clear();
                    }
                    _possible_moves.push_back(Move({pos.x + 2, pos.y - 2}, true,
                                         {pos.x + 1, pos.y - 1}, pos));
                    _killing_time = true;
                }
            }
        }
        if (pos.x - 1 >= 0 && pos.y + 1 < 8) {
            if (_checkers[pos.x - 1][pos.y + 1] != nullptr &&
                _checkers[pos.x - 1][pos.y + 1]->getSide() != _checkers[pos.x][pos.y]->getSide()) {
                if (pos.x - 2 >= 0 && pos.y + 2 < 8 && _checkers[pos.x - 2][pos.y + 2] == nullptr) {
                    if (!_killing_time) {
                        _possible_moves.clear();
                    }
                    _possible_moves.push_back(Move({pos.x - 2, pos.y + 2}, true,
                                         {pos.x - 1, pos.y + 1}, pos));
                    _killing_time = true;
                }
            }
        }
        if (pos.x + 1 < 8 && pos.y + 1 < 8) {
            if (_checkers[pos.x + 1][pos.y + 1] != nullptr &&
                _checkers[pos.x + 1][pos.y + 1]->getSide() != _checkers[pos.x][pos.y]->getSide()) {
                if (pos.x + 2 < 8 && pos.y + 2 < 8 && _checkers[pos.x + 2][pos.y + 2] == nullptr) {
                    if (!_killing_time) {
                        _possible_moves.clear();
                    }
                    _possible_moves.push_back(Move({pos.x + 2, pos.y + 2}, true,
                                         {pos.x + 1, pos.y + 1}, pos));
                    _killing_time = true;
                }
            }
        }

        if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && !_killing_time) {
            if (_checkers[pos.x - 1][pos.y - 1] == nullptr && _checkers[pos.x][pos.y]->getSide() == 1) {
                _possible_moves.push_back(Move({pos.x - 1, pos.y - 1}, false,
                                               { pos.x - 1, pos.y - 1}, pos));
            }
        }
        if (pos.x + 1 < 8 && pos.y - 1 >= 0 && !_killing_time) {
            if (_checkers[pos.x + 1][pos.y - 1] == nullptr && _checkers[pos.x][pos.y]->getSide() == 0) {
                _possible_moves.push_back(Move({pos.x + 1, pos.y - 1}, false,
                                               {pos.x + 1, pos.y - 1}, pos));
            }
        }
        if (pos.x - 1 >= 0 && pos.y + 1 < 8 && !_killing_time) {
            if (_checkers[pos.x - 1][pos.y + 1] == nullptr && _checkers[pos.x][pos.y]->getSide() == 1) {
                _possible_moves.push_back(Move({pos.x - 1, pos.y + 1}, false,
                                               {pos.x - 1, pos.y + 1}, pos));
            }
        }
        if (pos.x + 1 < 8 && pos.y + 1 < 8 && !_killing_time) {
            if (_checkers[pos.x + 1][pos.y + 1] == nullptr && _checkers[pos.x][pos.y]->getSide() == 0) {
                _possible_moves.push_back(Move({pos.x + 1, pos.y + 1}, false,
                                     {pos.x + 1, pos.y + 1}, pos));
            }
        }

        return _possible_moves;
    }

    std::vector<Move> getAllMoves(int side, bool practice = false) {
        _killing_time = false;
        //_possible_moves.clear();
        for (int i = 0; i < _checkers.size(); ++i) {
            for (int j = 0; j < _checkers[i].size(); ++j) {
                if (_checkers[i][j] && _checkers[i][j]->getSide() == side) {
                    getMovesForOne({i, j}, practice);
                }
            }
        }
        return _possible_moves;
    }

    void draw(sf::RenderWindow& window) const {
        for (int i = 0; i < _checkers.size(); ++i) {
            for (auto j : _checkers[i]) {
                if (j) {
                    j->draw(window);
                }
            }
        }
    }

    Checker* posCheck(sf::Vector2f pos) {
        for (int i = 0; i < _checkers.size(); ++i) {
            for (int j = 0; j < _checkers[i].size(); ++j) {
                if (_checkers[i][j] && _checkers[i][j]->contains(pos)) {
                    _checkers[i][j]->setArrPos({i, j});
                    return _checkers[i][j];
                }
            }
        }
        return nullptr;
    }

    bool makeMove(Move move, std::vector<std::vector<Dummy*>>& dummies, bool& moving_side) {

         _checkers[move.pos_start.x][move.pos_start.y]->changePos(dummies[move.pos_end.x][move.pos_end.y]->getPos());

        std::swap(_checkers[move.pos_start.x][move.pos_start.y], _checkers[move.pos_end.x][move.pos_end.y]);
        if (move.kill) {
            Checker* to_delete = _checkers[move.target.x][move.target.y];
            _checkers[move.target.x][move.target.y] = nullptr;
            delete to_delete;
            //ResetDummies(dummies);
            //IsItTimeToKill(checkers);
            getMovesForOne({move.pos_end.x,move.pos_end.y}, false, true);
            if (move.pos_end.x == 7 && !moving_side || move.pos_end.x == 0 && moving_side) {
                _checkers[move.pos_end.x][move.pos_end.y]->becomeQueen();
                moving_side = !moving_side;
                return true;
            }
            if (!_killing_time) {
                moving_side = !moving_side;
                //getAllMoves(moving_side);
            }

            //std::swap(_checkers[move.pos_start.x][move.pos_start.y], _checkers[move.pos_end.x][move.pos_end.y]);
            return true;
        }
        if (move.pos_end.x == 7 && moving_side || move.pos_end.x == 0 && !moving_side) {
            _checkers[move.pos_end.x][move.pos_end.y]->becomeQueen();
        }
        //ResetDummies(dummies);
        moving_side = !moving_side;
        //getAllMoves(moving_side);
        return true;
    }

    bool playerMove(std::vector<std::vector<Dummy*>>& dummies, sf::Vector2i selected, sf::Vector2f pos,
                    bool& moving_side) {
        for (int i = 0; i < dummies.size(); ++i) {
            for (int j = 0; j < dummies.size(); ++j) {
                if (dummies[i][j]->isActivated() && dummies[i][j]->contains(pos)) {
                    if (i == 7 && !moving_side || i == 0 && moving_side) {
                        _checkers[selected.x][selected.y]->becomeQueen();
                    }
                    _checkers[selected.x][selected.y]->changePos(dummies[i][j]->getPos());
                    std::swap(_checkers[selected.x][selected.y], _checkers[i][j]);
                    if (dummies[i][j]->isToKill()) {
                        Checker* to_delete = _checkers[dummies[i][j]->getTarget().x][dummies[i][j]->getTarget().y];
                        _checkers[dummies[i][j]->getTarget().x][dummies[i][j]->getTarget().y] = nullptr;
                        delete to_delete;
                        //ResetDummies(dummies);
                        //IsItTimeToKill(checkers);
                        getMovesForOne({i, j}, false, true);
                        if (!_killing_time) {
                            moving_side = !moving_side;
                            getAllMoves(moving_side);
                        }
                        return true;
                    }
                    //ResetDummies(dummies);
                    moving_side = !moving_side;
                    getAllMoves(moving_side);
                    return true;
                }
            }
        }
        return false;
    }

    bool practiceMove(Move move, bool& moving_side) {

        //_checkers[move.pos_start.x][move.pos_start.y]->changePos(dummies[move.pos_end.x][move.pos_end.y]->getPos());
        if (_checkers[move.pos_start.x][move.pos_start.y] == nullptr) {
            std::cout << "HOW2\n";
        }
        std::swap(_checkers[move.pos_start.x][move.pos_start.y], _checkers[move.pos_end.x][move.pos_end.y]);
        if (move.kill) {
            Checker* to_delete = _checkers[move.target.x][move.target.y];
            _checkers[move.target.x][move.target.y] = nullptr;
           // delete to_delete;
            //ResetDummies(dummies);
            //IsItTimeToKill(checkers);
            getMovesForOne({move.pos_end.x,move.pos_end.y}, true, true);
            if (!_killing_time) {
                moving_side = !moving_side;
                getAllMoves(moving_side);
            }
            if (move.pos_end.x == 7 && !moving_side || move.pos_end.x == 0 && moving_side) {
                _checkers[move.pos_end.x][move.pos_end.y]->becomeFakeQueen();
                moving_side = !moving_side;
            }
            //std::swap(_checkers[move.pos_start.x][move.pos_start.y], _checkers[move.pos_end.x][move.pos_end.y]);
            return true;
        }
        if (move.pos_end.x == 7 || move.pos_end.x == 0) {
            _checkers[move.pos_end.x][move.pos_end.y]->becomeFakeQueen();
        }
        //ResetDummies(dummies);
        moving_side = !moving_side;
        //getAllMoves(moving_side);
        return true;
    }

    void clearPossibleMoves() {
        _possible_moves.clear();
    }

 private:
    sf::Color _black_piece_color, _white_piece_color;
    std::vector<std::vector<Checker*>> _checkers;
    std::vector<Move> _possible_moves;
    bool _killing_time = false;
};
