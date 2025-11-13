/**
 * @file Numerical_Classes.h
 * @brief Defines the Numerical Tic-Tac-Toe specific classes.
 *
 * This file provides:
 * - `Numerical_Board`: A specialized board class for Numerical Tic-Tac-Toe.
 * - `Numerical_UI`: A user interface class for the game.
 */

#ifndef NUMERICAL_CLASSES_H
#define NUMERICAL_CLASSES_H

#include "BoardGame_Classes.h"
#include <set>
using namespace std;


class Numerical_Board : public Board<int> {
private:
    int blank_symbol = 0;

public:
    Numerical_Board();

    bool update_board(Move<int>* move);
    bool is_win(Player<int>* player);
    bool is_lose(Player<int>*) { return false; }
    bool is_draw(Player<int>* player);
    bool game_is_over(Player<int>* player);
};

class Numerical_Player : public Player<int> {
private:
    set<int> available_numbers;

public:
    Numerical_Player(string n, int s, PlayerType t, set<int> nums);
    set<int> get_available_numbers() const { return available_numbers; }

    bool use_number(int num);
    void return_number(int num);
};

class Numerical_UI : public UI<int> {
public:
    Numerical_UI();

    ~Numerical_UI() {}

    Player<int>* create_player(string& name, int symbol, PlayerType type);

    Move<int>* get_move(Player<int>* player);
    Player<int>** setup_players();
};

#endif // NUMERICAL_CLASSES_H