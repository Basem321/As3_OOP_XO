
#pragma once

#include "BoardGame_Classes.h"

class TicTacToe5x5 : public Board<char> {
public:
    TicTacToe5x5 ();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

   
    int count_three_in_a_row(char symbol);
};

class TicTacToe5x5_UI : public UI<char> {
public:
    TicTacToe5x5_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};
