#ifndef OBSTACLES_TIC_TAC_TOE_H
#define OBSTACLES_TIC_TAC_TOE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

#include "BoardGame_Classes.h"

using namespace std;

class Obstacles_Tic_Tac_Toe_Board : public Board<char> {
public:
    static const int ROWS = 6;
    static const int COLS = 6;

    Obstacles_Tic_Tac_Toe_Board();
    virtual ~Obstacles_Tic_Tac_Toe_Board() override = default;
    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;


    void add_random_obstacles(int n = 2);
    void clear_board();
    vector<pair<int, int>> get_empty_cells() const;

private:
    bool four_in_a_row_from(int r, int c, char sym) const;
    bool board_full() const;
    int moves_this_round = 0;
};

class Obstacles_Tic_Tac_Toe_UI : public UI<char> {
public:
    Obstacles_Tic_Tac_Toe_UI() : UI<char>("Obstacles Tic-Tac-Toe UI", 2) {}
    virtual ~Obstacles_Tic_Tac_Toe_UI() override = default;

    virtual Move<char>* get_move(Player<char>* player) override;
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif // OBSTACLES_TIC_TAC_TOE_H