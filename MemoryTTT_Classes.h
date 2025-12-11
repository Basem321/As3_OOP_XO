#ifndef MEMORY_Tic_Tac_Toe_CLASSES_H
#define MEMORY_Tic_Tac_Toe_CLASSES_H

#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>
using namespace std;

class MemoryTTT_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<vector<char>> display_board;

public:
    MemoryTTT_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    vector<vector<char>> get_display_board() const { return display_board; }
};

class MemoryTTT_AI_Player : public Player<char> {
private:
    static const int MAX_DEPTH = 9;

    bool check_win(vector<vector<char>>& board, char sym) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
                return true;
        }
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym)
                return true;
        }
        if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym)
            return true;
        if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
            return true;
        return false;
    }

    vector<pair<int, int>> get_valid_moves(vector<vector<char>>& board) {
        vector<pair<int, int>> moves;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '.') {
                    moves.push_back({ i, j });
                }
            }
        }
        return moves;
    }

    int minimax(vector<vector<char>>& board, int depth, bool is_maximizing, int alpha, int beta) {
        if (check_win(board, this->symbol)) return 10 - depth;
        if (check_win(board, get_opponent_symbol())) return depth - 10;
        vector<pair<int, int>> moves = get_valid_moves(board);
        if (moves.empty()) return 0;

        if (is_maximizing) {
            int max_eval = numeric_limits<int>::min();
            for (auto& move : moves) {
                board[move.first][move.second] = this->symbol;
                int eval = minimax(board, depth + 1, false, alpha, beta);
                board[move.first][move.second] = '.';
                max_eval = max(max_eval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) break;
            }
            return max_eval;
        }
        else {
            int min_eval = numeric_limits<int>::max();
            char opp = get_opponent_symbol();
            for (auto& move : moves) {
                board[move.first][move.second] = opp;
                int eval = minimax(board, depth + 1, true, alpha, beta);
                board[move.first][move.second] = '.';
                min_eval = min(min_eval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) break;
            }
            return min_eval;
        }
    }

    char get_opponent_symbol() {
        return (this->symbol == 'X') ? 'O' : 'X';
    }

public:
    MemoryTTT_AI_Player(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::AI) {}

    Move<char>* get_best_move() {
        vector<vector<char>> board = this->boardPtr->get_board_matrix();
        int best_score = numeric_limits<int>::min();
        pair<int, int> best_move = { -1, -1 };
        vector<pair<int, int>> moves = get_valid_moves(board);

        for (auto& move : moves) {
            board[move.first][move.second] = this->symbol;
            int score = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
            board[move.first][move.second] = '.';

            if (score > best_score) {
                best_score = score;
                best_move = move;
            }
        }

        cout << this->name << " (AI) plays at (" << best_move.first << "," << best_move.second << ")\n";
        return new Move<char>(best_move.first, best_move.second, this->symbol);
    }
};

class MemoryTTT_UI : public UI<char> {
public:
    MemoryTTT_UI();
    ~MemoryTTT_UI() {}
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const;
    void display_memory_board(MemoryTTT_Board* board);
    Player<char>** setup_players() override;
};

#endif