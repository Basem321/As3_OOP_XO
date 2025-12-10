#ifndef ULTIMATE_TICTACTOE_H
#define ULTIMATE_TICTACTOE_H

#include "BoardGame_Classes.h"

class MiniBoard : public Board<char> {
private:
    char blank_symbol = '.';

public:
    MiniBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void reset();
    char check_winner();
};

class UltimateTicTacToe_Board : public Board<char> {
private:
    MiniBoard mini_board_X;
    MiniBoard mini_board_O;
    char main_board[3][3];
    int active_board_x;
    int active_board_y;
    bool first_move;
    Player<char>* current_player;
    bool sub_game_in_progress;
    int last_cell_x;
    int last_cell_y;

    bool check_main_board_win(char symbol);
    bool is_main_board_full();

public:
    UltimateTicTacToe_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    void start_sub_game(int board_x, int board_y, Player<char>* player);
    void end_sub_game();
    MiniBoard* get_current_mini_board();
    int get_active_board_x() const { return active_board_x; }
    int get_active_board_y() const { return active_board_y; }
    bool is_first_move() const { return first_move; }
    bool is_sub_game_in_progress() const { return sub_game_in_progress; }
    char get_main_board_cell(int x, int y) const { return main_board[x][y]; }
    char& get_main_board_cell_ref(int x, int y) { return main_board[x][y]; }
    bool is_position_available(int x, int y) const { return main_board[x][y] == 0; }
};

class UltimateTicTacToe_UI : public UI<char> {
public:
    UltimateTicTacToe_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

    void display_main_board(UltimateTicTacToe_Board* board);
    void display_mini_board(MiniBoard* mini_board, int board_x, int board_y);
};

#endif