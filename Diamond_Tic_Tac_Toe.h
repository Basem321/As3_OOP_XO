#ifndef DIAMOND_TIC_TAC_TOE_H
#define DIAMOND_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;


class Diamond_Tic_Tac_Toe_Board : public Board<char> {
public:
    Diamond_Tic_Tac_Toe_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool inside_diamond(int r, int c);

private:
    bool check_line(char sym, int r, int c, int dr, int dc, int needed);
};


class Diamond_AI_Player : public Player<char> {
public:
    Diamond_AI_Player(string n, char s) : Player<char>(n, s, PlayerType::AI) {}
    Move<char>* get_ai_move();
};


class Diamond_Tic_Tac_Toe_UI : public UI<char> {
public:
    Diamond_Tic_Tac_Toe_UI() : UI<char>("\n--- Diamond Tic Tac Toe ---", 2) {}

    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI)
            return dynamic_cast<Diamond_AI_Player*>(player)->get_ai_move();

        int r, c;
        cout << player->get_name() << " (" << player->get_symbol()
            << ") enter row and column: ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::AI || type == PlayerType::COMPUTER)
            return new Diamond_AI_Player(name, symbol);

        return new Player<char>(name, symbol, PlayerType::HUMAN);
    }

    void display_board_matrix(const vector<vector<char>>& mat) const ;
};

#endif