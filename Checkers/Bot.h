#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Checker.h"
#include "Move.h"
#include "CheckArr.h"

class Bot {
 public:
    explicit Bot(int side) : _side(side) { }
    virtual Move makeMove(CheckArr& checkArr) = 0;
    virtual bool isToMove() final {
        return _additional_move;
    }
 protected:
    int _side;
    bool _additional_move = false;
};

class EasyBot : public Bot {
 public:
    explicit EasyBot(int side) : Bot(side) { }
    Move makeMove(CheckArr& checkArr) override {
        std::vector<Move> moves = checkArr.getAllMoves(_side);
        checkArr.clearPossibleMoves();
        if (moves.empty()) {
            return Move();
        }
        _additional_move = checkArr.isTimeToKill();
        return moves[std::rand() % moves.size()];
    }
};

class DifficultBot : public Bot {
 public:
    explicit DifficultBot(int side) : Bot(side) { }
    Move makeMove(CheckArr& checkArr) override {
        std::cout << "Thinking\n";
        std::vector<Move> moves = checkArr.getAllMoves(_side);
        if (moves.empty()) {
            return Move();
        }
        Move ans = moves[0];
        int ans_n = 0;
        bool f = false;
        for (auto a : moves) {
            CheckArr arr = checkArr;
            bool tmp_side = _side;
            int tmp_ans = 0;
            if (a.kill) {
                ++tmp_ans;
            }
            if (!arr.getChecker(a.pos_start)->isQueen() &&
            (a.pos_end.x == 7 && !_side || a.pos_end.x == 0 && _side)) {
                ans = a;
                break;
            }
            arr.practiceMove(a, tmp_side);
            if (tmp_side == _side) {
                tmp_ans += scan(arr, tmp_side);
            }
            else {
                tmp_ans -= scan(arr, tmp_side);
            }
            if (!f || tmp_ans > ans_n){
                ans_n = tmp_ans;
                ans = a;
            }
            f = true;
        }
        checkArr.clearPossibleMoves();
        std::cout << "Done thinking\n";
        return ans;
    }

    int scan(CheckArr& checkArr, bool side, int depth = 0) {
        if (depth > 4) {
            return 0;
        }
//        checkArr.clearPossibleMoves();
        int ans = 0;
        bool f = false;


        CheckArr arr = checkArr;
        arr.clearPossibleMoves();
        std::vector<Move> moves = arr.getAllMoves(_side);
        for (auto a : moves) {
            arr = checkArr;
            arr.clearPossibleMoves();
            bool tmp_side = side;
            int tmp_ans = 0;
            if (a.kill) {
                ++tmp_ans;
            }
            if (!arr.getChecker(a.pos_start)->isQueen() &&
            (a.pos_end.x == 7 && !_side || a.pos_end.x == 0 && _side)) {
                ans += 4;
                break;
            }
            arr.practiceMove(a, tmp_side);
            if (tmp_side == side) {
                tmp_ans += scan(arr, tmp_side, depth + 1);
            }
            else {
                tmp_ans -= scan(arr, tmp_side, depth + 1);
            }
            if (!f || tmp_ans > ans){
                ans = tmp_ans;
            }
            f = true;
        }
        return ans;
    }
};

class MediumBot : public Bot {
 public:
    explicit MediumBot(int side) : Bot(side) { }
    Move makeMove(CheckArr& checkArr) override {
        std::cout << "Thinking\n";
        std::vector<Move> moves = checkArr.getAllMoves(_side);
        if (moves.empty()) {
            return Move();
        }
        Move ans = moves[0];
        int ans_n = 0;
        bool f = false;
        for (auto a : moves) {
            CheckArr arr = checkArr;
            bool tmp_side = _side;
            int tmp_ans = 0;
            if (a.kill) {
                ++tmp_ans;
            }
            if (a.pos_end.x == 7 && !_side || a.pos_end.x == 0 && _side) {
                ans = a;
                break;
            }
            arr.practiceMove(a, tmp_side);
            if (tmp_side == _side) {
                tmp_ans += scan(arr, tmp_side);
            }
            else {
                tmp_ans -= scan(arr, tmp_side);
            }
            if (!f || tmp_ans > ans_n){
                ans_n = tmp_ans;
                ans = a;
            }
            f = true;
        }
        checkArr.clearPossibleMoves();
        std::cout << "Done thinking\n";
        return ans;
    }

    int scan(CheckArr& checkArr, bool side, int depth = 0) {
        if (depth > 2) {
            return 0;
        }
//        checkArr.clearPossibleMoves();
        int ans = 0;
        bool f = false;


        CheckArr arr = checkArr;
        arr.clearPossibleMoves();
        std::vector<Move> moves = arr.getAllMoves(_side);
        for (auto a : moves) {
            arr = checkArr;
            arr.clearPossibleMoves();
            bool tmp_side = side;
            int tmp_ans = 0;
            if (a.kill) {
                ++tmp_ans;
            }
            if (a.pos_end.x == 7 /*&& _side*/ || a.pos_end.x == 0 /*&& !_side*/) {
                ans += 4;
                break;
            }
            arr.practiceMove(a, tmp_side);
            if (tmp_side == side) {
                tmp_ans += scan(arr, tmp_side, depth + 1);
            }
            else {
                tmp_ans -= scan(arr, tmp_side, depth + 1);
            }
            if (!f || tmp_ans > ans){
                ans = tmp_ans;
            }
            f = true;
        }
        return ans;
    }
};
