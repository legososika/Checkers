#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Checker.h"
#include "Dummy.h"
#include "Move.h"
#include "Bot.h"
#include "CheckArr.h"

sf::Color background_color = sf::Color(20, 20, 20),
white_piece_color = sf::Color(255,248,220),
black_piece_color = sf::Color(218,165,32);

bool killing_time = false;
bool killing_spree = false;
bool moving_side = 1;
bool respond_time = false;
bool game_over = false;

sf::Texture board_texture;

sf::Font font;


//
//std::vector<Move> GetAllMoves(std::vector<std::vector<Checker*>>& checkers, sf::Vector2i pos) {
//    std::vector<Move> moves;
//    if (pos.x - 1 >= 0 && pos.y - 1 >= 0) {
//        if (checkers[pos.x - 1][pos.y - 1] != nullptr &&
//        checkers[pos.x - 1][pos.y - 1]->getSide() != checkers[pos.x][pos.y]->getSide()) {
//            if (pos.x - 2 >= 0 && pos.y - 2 >= 0 && checkers[pos.x - 2][pos.y - 2] == nullptr) {
//                moves.push_back(Move({pos.x - 2, pos.y - 2}, true,
//                                     {pos.x - 1, pos.y - 1}));
//            }
//        }
//        if (checkers[pos.x - 1][pos.y - 1] == nullptr && checkers[pos.x][pos.y]->getSide() == 1) {
//            moves.push_back(Move({pos.x - 1, pos.y - 1}, false,
//                                 { pos.x - 1, pos.y - 1}));
//        }
//    }
//    if (pos.x + 1 < 8 && pos.y - 1 >= 0) {
//        if (checkers[pos.x + 1][pos.y - 1] != nullptr &&
//            checkers[pos.x + 1][pos.y - 1]->getSide() != checkers[pos.x][pos.y]->getSide()) {
//            if (pos.x + 2 < 8 && pos.y - 2 >= 0 && checkers[pos.x + 2][pos.y - 2] == nullptr) {
//                moves.push_back(Move({pos.x + 2, pos.y - 2}, true,
//                                     {pos.x + 1, pos.y - 1}));
//            }
//        }
//        if (checkers[pos.x + 1][pos.y - 1] == nullptr && checkers[pos.x][pos.y]->getSide() == 0) {
//            moves.push_back(Move({pos.x + 1, pos.y - 1}, false,
//                                 {pos.x + 1, pos.y - 1}));
//        }
//    }
//    if (pos.x - 1 >= 0 && pos.y + 1 < 8) {
//        if (checkers[pos.x - 1][pos.y + 1] != nullptr &&
//            checkers[pos.x - 1][pos.y + 1]->getSide() != checkers[pos.x][pos.y]->getSide()) {
//            if (pos.x - 2 >= 0 && pos.y + 2 < 8 && checkers[pos.x - 2][pos.y + 2] == nullptr) {
//                moves.push_back(Move({pos.x - 2, pos.y + 2}, true,
//                                     {pos.x - 1, pos.y + 1}));
//            }
//        }
//        if (checkers[pos.x - 1][pos.y + 1] == nullptr && checkers[pos.x][pos.y]->getSide() == 1) {
//            moves.push_back(Move({pos.x - 1, pos.y + 1}, false,
//                                 {pos.x - 1, pos.y + 1}));
//        }
//    }
//    if (pos.x + 1 < 8 && pos.y + 1 < 8) {
//        if (checkers[pos.x + 1][pos.y + 1] != nullptr &&
//            checkers[pos.x + 1][pos.y + 1]->getSide() != checkers[pos.x][pos.y]->getSide()) {
//            if (pos.x + 2 < 8 && pos.y + 2 < 8 && checkers[pos.x + 2][pos.y + 2] == nullptr) {
//                moves.push_back(Move({pos.x + 2, pos.y + 2}, true,
//                                     {pos.x + 1, pos.y + 1}));
//            }
//        }
//        if (checkers[pos.x + 1][pos.y + 1] == nullptr && checkers[pos.x][pos.y]->getSide() == 0) {
//            moves.push_back(Move({pos.x + 1, pos.y + 1}, false,
//                                 {pos.x + 1, pos.y + 1}));
//        }
//    }
//    return moves;
//}
//done

//void IsItTimeToKill(std::vector<std::vector<Checker*>>& checkers) {
//    for (int i = 0; i < checkers.size(); ++i) {
//        for (int j = 0; j < checkers[i].size(); ++j) {
//            if (checkers[i][j] && checkers[i][j]->getSide() == moving_side) {
//                std::vector<Move> moves = GetAllMoves(checkers, {i, j});
//                for (auto a : moves) {
//                    if (a.kill) {
//                        killing_time = true;
//                        return;
//                    }
//                }
//            }
//        }
//    }
//    killing_time = false;
//} //not sure

void LoadTextures() {
    if (!board_texture.loadFromFile("/Users/Neponel/CLionProjects/Checkers/Board.png")) {
        std::cout << "Failed loading board texture";
        throw;
    }
    if (!font.loadFromFile("/Users/Neponel/CLionProjects/Checkers/UbuntuMono-Regular.ttf")) {
        std::cout << "Failed loading font";
        throw;
    }
}

void SetupBoard(sf::Sprite& board) {
    board.setTexture(board_texture);
    board.setColor(sf::Color(245,222,179));
    board.setPosition(2200 / 2 - 512, 1500 / 2 - 512);
    board.setScale(0.5f, 0.5f);
}

//void SetupCheckers(std::vector<std::vector<Checker*>>& checkers) {
//    int x_ch = 615, y_ch = 260;
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0 + 1 - i % 2; j < 8; j += 2) {
//            checkers[i][j] = new Checker({float(0 + j * 128 + x_ch), float(0 + i * 128 + y_ch)},
//                                         0, black_piece_color);
//        }
//    }
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0 + i % 2; j < 8; j += 2) {
//            checkers[7 - i][j] = new Checker({float(0 + j * 128 + x_ch), float(0 + (7 - i) * 128 + y_ch)},
//                                         1, white_piece_color);
//        }
//    }
//} //done

void SetupDummies(std::vector<std::vector<Dummy*>>& dummies) {
    int x_ch = 615, y_ch = 260;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            dummies[i][j] = new Dummy({float(j * 128 + x_ch), float(i * 128 + y_ch)});
        }
    }
}

//void ResetPositions(std::vector<std::vector<Checker*>>& checkers) {
//    for (int i = 0; i < checkers.size(); ++i) {
//        for (auto j : checkers[i]) {
//            if (j) {
//                Checker* to_delete = j;
//                j = nullptr;
//                delete to_delete;
//            }
//        }
//    }
//    SetupCheckers(checkers);
//} //done

void ResetScore() {

}

void ResetDummies(std::vector<std::vector<Dummy*>>& dummies) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            dummies[i][j]->setActivation(0);
            dummies[i][j]->setKill(0);
        }
    }
}

void ResetAI() {

}

void StartGame(CheckArr& checkArr, std::vector<std::vector<Dummy*>>& dummies) {
    checkArr.reset();
    ResetScore();
    ResetDummies(dummies);
    ResetAI();
}



void Click(sf::Vector2f pos, std::vector<std::vector<Dummy*>>& dummies, sf::Vector2i& selected,
           CheckArr& checkArr) {

//    for (int i = 0; i < dummies.size(); ++i) {
//        for (int j = 0; j < dummies.size(); ++j) {
//            if (dummies[i][j]->isActivated() && dummies[i][j]->contains(pos)) {
//                if (i == 7 || i == 0) {
//                    checkers[selected.x][selected.y]->becomeQueen();
//                }
//                checkers[selected.x][selected.y]->changePos(dummies[i][j]->getPos());
//                std::swap(checkers[selected.x][selected.y], checkers[i][j]);
//                if (dummies[i][j]->isToKill()) {
//                    Checker* to_delete = checkers[dummies[i][j]->getTarget().x][dummies[i][j]->getTarget().y];
//                    checkers[dummies[i][j]->getTarget().x][dummies[i][j]->getTarget().y] = nullptr;
//                    delete to_delete;
//                    ResetDummies(dummies);
//                    IsItTimeToKill(checkers);
//                    if (!killing_time) {
//                        moving_side = !moving_side;
//                        IsItTimeToKill(checkers);
//                    }
//                    return;
//                }
//                ResetDummies(dummies);
//                moving_side = !moving_side;
//                IsItTimeToKill(checkers);
//                return;
//            }
//        }
//    }
    bool prev_side = moving_side;
    if (checkArr.playerMove(dummies, selected, pos, moving_side)) {
        ResetDummies(dummies);
        if (prev_side != moving_side) {
            respond_time = true;
        }
        checkArr.clearPossibleMoves();
        return;
    }
    ResetDummies(dummies);
    Checker* check = checkArr.posCheck(pos);
    if (check && check->getSide() == moving_side) {
        selected = check->getArrPos();
        std::vector<Move> moves = checkArr.getMovesForOne(selected, false, false, true);
        for (auto a : moves) {
            if (!checkArr.isTimeToKill() || checkArr.isTimeToKill() == a.kill) {
                dummies[a.pos_end.x][a.pos_end.y]->setActivation(1);
                dummies[a.pos_end.x][a.pos_end.y]->setKill(a.kill);
                dummies[a.pos_end.x][a.pos_end.y]->setTarget(a.target);
                std::cout << a.pos_end.x << " " << a.pos_end.y << '\n';
            }
        }
        return;
    }
//    for (int i = 0; i < checkers.size(); ++i) {
//        for (int j = 0; j < checkers[i].size(); ++j) {
//            if (checkers[i][j] != nullptr && checkers[i][j]->contains(pos) &&
//            checkers[i][j]->getSide() == moving_side) {
//                selected = {i, j};
//                std::vector<Move> moves = GetAllMoves(checkers, {i, j});
//
//                for (auto a : moves) {
//                    if (!killing_time || killing_time == a.kill) {
//                        dummies[a.pos_end.x][a.pos_end.y]->setActivation(1);
//                        dummies[a.pos_end.x][a.pos_end.y]->setKill(a.kill);
//                        dummies[a.pos_end.x][a.pos_end.y]->setTarget(a.target);
//                        std::cout << a.pos_end.x << " " << a.pos_end.y << '\n';
//                    }
//                }
//                return;
//            }
//        }
//    }

}

void Respond(CheckArr& checkArr, Bot* the_bot, std::vector<std::vector<Dummy*>>& dummies) {
    Move bot_move = the_bot->makeMove(checkArr);
    if (bot_move.pos_end.x == -1) {
        game_over = true;
        return;
    }
    checkArr.makeMove(bot_move, dummies, moving_side);
}

//void DrawCheckers(sf::RenderWindow& window, std::vector<std::vector<Checker*>>& checkers) {
//    for (int i = 0; i < checkers.size(); ++i) {
//        for (auto j : checkers[i]) {
//            if (j) {
//                j->draw(window);
//            }
//        }
//    }
//} //done

void DrawDummies(sf::RenderWindow& window, std::vector<std::vector<Dummy*>>& dummies){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (dummies[i][j]->isActivated()) {
                dummies[i][j]->draw(window);
            }
        }
    }
}

int main() {
    LoadTextures();

    sf::RenderWindow window(sf::VideoMode(2200, 1500), "Checkers");

    sf::Sprite board;
    std::vector<std::vector<Checker*>> checkers(8, std::vector<Checker*>(8, nullptr));
    std::vector<std::vector<Dummy*>> dummies(8, std::vector<Dummy*>(8));
    Bot* botte = new DifficultBot(0);

    CheckArr checkArr(black_piece_color, white_piece_color);

    sf::Text bot_easy_text, bot_medium_text, bot_hard_text;

    bot_easy_text.setFont(font);
    bot_easy_text.setString("Easy");
    bot_easy_text.setScale(5, 5);
    bot_easy_text.setPosition(100, 100);

    bot_medium_text.setFont(font);
    bot_medium_text.setString("Medium");
    bot_medium_text.setScale(5, 5);
    bot_medium_text.setPosition(100, 300);

    bot_hard_text.setFont(font);
    bot_hard_text.setString("Hard");
    bot_hard_text.setScale(5, 5);
    bot_hard_text.setPosition(100, 500);
    bot_hard_text.setFillColor(sf::Color::Cyan);

    sf::Text game_over_text;

    game_over_text.setFont(font);
    game_over_text.setString("Game Over");
    game_over_text.setScale(5, 5);
    game_over_text.setPosition(750, 600);
    game_over_text.setFillColor(sf::Color::Red);
    //Checker* atest = new Checker({750, 300}, 1, black_piece_color);
//    sf::CircleShape btest;
//    btest.setRadius(10);
//    btest.setFillColor(white_piece_color);
//    btest.setPosition({750, 300});
//    btest.setRadius(10);

//    btest.setFillColor(white_piece_color);
//    btest.setOutlineColor(black_piece_color);

    SetupBoard(board);
    SetupDummies(dummies);
    checkArr.setup(615, 260);

    //checkers[0][0]->changePos({750, 300});
    sf::Vector2i selected = {0, 0};

    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (bot_easy_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        delete botte;
                        botte = new EasyBot(0);
                        bot_easy_text.setFillColor(sf::Color::Cyan);
                        bot_medium_text.setFillColor(sf::Color::White);
                        bot_hard_text.setFillColor(sf::Color::White);
                        StartGame(checkArr, dummies);
                        game_over = false;
                        break;
                    }
                    if (bot_medium_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        delete botte;
                        botte = new MediumBot(0);
                        bot_easy_text.setFillColor(sf::Color::White);
                        bot_medium_text.setFillColor(sf::Color::Cyan);
                        bot_hard_text.setFillColor(sf::Color::White);
                        StartGame(checkArr, dummies);
                        game_over = false;
                        break;
                    }
                    if (bot_hard_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        delete botte;
                        botte = new DifficultBot(0);
                        bot_easy_text.setFillColor(sf::Color::White);
                        bot_medium_text.setFillColor(sf::Color::White);
                        bot_hard_text.setFillColor(sf::Color::Cyan);
                        StartGame(checkArr, dummies);
                        game_over = false;
                        break;
                    }
                    Click({(float)event.mouseButton.x, (float)event.mouseButton.y},dummies,
                          selected, checkArr);

                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::R) {
                        StartGame(checkArr, dummies);
                        game_over = false;
                    }

                default:
                    break;
            }
        }

        window.clear(background_color);

        window.draw(board);
        DrawDummies(window, dummies);
        checkArr.draw(window);
        window.draw(bot_easy_text);
        window.draw(bot_medium_text);
        window.draw(bot_hard_text);
        if (game_over) {
            window.draw(game_over_text);
        }

//        DrawCheckers(window, checkers);
//        window.draw(checkers[0][0]->getSprite());
//        window.draw(atest.getSprite());
//        window.draw(btest);


        window.display();
        int i = 0;
        while (respond_time && i < 3) {
            ++i;
            bool prev_side = moving_side;

            sf::sleep(sf::seconds(0.2));
            Respond(checkArr, botte, dummies);

            window.clear(background_color);

            window.draw(board);
            DrawDummies(window, dummies);
            checkArr.draw(window);
            window.draw(bot_easy_text);
            window.draw(bot_medium_text);
            window.draw(bot_hard_text);
            window.display();
            if (prev_side != moving_side) {
                respond_time = false;
            }
        }
    }

    return 0;
}
