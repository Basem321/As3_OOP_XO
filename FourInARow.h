#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"

using namespace std;
class FourInARow_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int find_lowest_row(int col);

public:
    FourInARow_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};
class FourInARow_UI : public UI<char> {
public:
    FourInARow_UI();
    ~FourInARow_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // FOUR_IN_A_ROW_H