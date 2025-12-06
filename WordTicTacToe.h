#pragma once

#include "BoardGame_Classes.h"
#include <fstream>  
#include <string>
#include <set>    

using namespace std;

class WordTicTacToe_Board : public Board<char> {
private:
    set<string> dic; 
    char blank_symbol = 0;  

    
    void load_dic(const string& filename);

public:
    WordTicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};


class WordTicTacToe_UI : public UI<char> {
public:
    WordTicTacToe_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    Player<char>** setup_players() override; 
};