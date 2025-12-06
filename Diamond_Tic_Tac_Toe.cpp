#include "Diamond_Tic_Tac_Toe.h"
#include <iostream>
using namespace std;


Diamond_Tic_Tac_Toe_Board::Diamond_Tic_Tac_Toe_Board()
    : Board(7, 7)
{
    board.resize(7, vector<char>(7, '#'));

    int mid = 3;
    for (int r = 0; r < 7; r++) {
        int dist = abs(r - mid);
        int allowed = 7 - 2 * dist;  
        int start = mid - allowed / 2;

        for (int c = start; c < start + allowed; c++)
            board[r][c] = ' ';  
    }
}


bool Diamond_Tic_Tac_Toe_Board::inside_diamond(int r, int c) {
    int mid = 3;
    int dist = abs(r - mid);
    int allowed = 7 - 2 * dist;
    int start = mid - allowed / 2;
    int end = start + allowed - 1;

    return (c >= start && c <= end);
}



bool Diamond_Tic_Tac_Toe_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char s = move->get_symbol();

    if (r < 0 || r >= 7 || c < 0 || c >= 7) return false;
    if (!inside_diamond(r, c)) return false;
    if (board[r][c] != ' ') return false;

    board[r][c] = s;
    n_moves++;
    return true;
}



bool Diamond_Tic_Tac_Toe_Board::check_line(char sym, int r, int c, int dr, int dc, int needed) {
    for (int i = 0; i < needed; i++) {
        int rr = r + dr * i;
        int cc = c + dc * i;

        if (rr < 0 || rr >= 7 || cc < 0 || cc >= 7) return false;
        if (!inside_diamond(rr, cc)) return false;
        if (board[rr][cc] != sym) return false;
    }
    return true;
}



bool Diamond_Tic_Tac_Toe_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {
            if (!inside_diamond(r, c)) continue;

            if (check_line(sym, r, c, 1, 0, 4) ||
                check_line(sym, r, c, 0, 1, 4) ||
                check_line(sym, r, c, 1, 1, 4) ||
                check_line(sym, r, c, 1, -1, 4))
                return true;
        }
    }
    return false;
}


bool Diamond_Tic_Tac_Toe_Board::is_draw(Player<char>* player) {
    return n_moves == 25; 
}

bool Diamond_Tic_Tac_Toe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}



Move<char>* Diamond_AI_Player::get_ai_move() {
    auto mat = boardPtr->get_board_matrix();

    for (int r = 0; r < 7; r++)
        for (int c = 0; c < 7; c++)
            if (mat[r][c] == ' ' && abs(r - 3) + abs(c - 3) <= 3)
                return new Move<char>(r, c, symbol);

    return nullptr;
}



void Diamond_Tic_Tac_Toe_UI::display_board_matrix(const vector<vector<char>>& mat) const {
    system("cls");
    cout << "\n       ? DIAMOND TIC TAC TOE ?\n\n";

    int mid = 3;

    for (int r = 0; r < 7; r++) {

        int dist = abs(r - mid);
        int allowed = 7 - dist * 2;
        int start = mid - allowed / 2;

        cout << string(dist * 3, ' ');

        for (int c = start; c < start + allowed; c++) {
            cout << "[" << (mat[r][c] == ' ' ? ' ' : mat[r][c]) << "] ";
        }
        cout << "\n";
    }

    cout << endl;
}