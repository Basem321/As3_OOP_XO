#ifndef INFINITY_TICTACTOE_H
#define INFINITY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <queue>

using namespace std;

class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';
	queue<pair<int, int>> player_x_moves; //  i used queue to delete the oldest move FIFO (-+ _ -+) 
	queue<pair<int, int>> player_o_moves; // and for the pair to store the coordinates of the moves for the oldest move also it seems wired but it works
    int x_move_count = 0;
    int o_move_count = 0;

public:
    Infinity_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>*) override { return false; }
    bool game_is_over(Player<char>* player) override;
};

class Infinity_UI : public UI<char> {
public:
    Infinity_UI();
    ~Infinity_UI() {}
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif