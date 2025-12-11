#include "MemoryTTT_Classes.h"
#include <iostream>

MemoryTTT_Board::MemoryTTT_Board() : Board<char>(3, 3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->board[i][j] = blank_symbol;
        }
    }
    display_board = vector<vector<char>>(3, vector<char>(3, '?'));
    this->n_moves = 0;
}

bool MemoryTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (this->board[x][y] != blank_symbol) return false;

    this->board[x][y] = symbol;
    display_board[x][y] = '?';
    this->n_moves++;
    return true;
}

bool MemoryTTT_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    for (int i = 0; i < 3; i++) {
        if (this->board[i][0] == symbol &&
            this->board[i][1] == symbol &&
            this->board[i][2] == symbol) {
            return true;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (this->board[0][j] == symbol &&
            this->board[1][j] == symbol &&
            this->board[2][j] == symbol) {
            return true;
        }
    }

    if (this->board[0][0] == symbol &&
        this->board[1][1] == symbol &&
        this->board[2][2] == symbol) {
        return true;
    }

    if (this->board[0][2] == symbol &&
        this->board[1][1] == symbol &&
        this->board[2][0] == symbol) {
        return true;
    }

    return false;
}

bool MemoryTTT_Board::is_draw(Player<char>* player) {
    if (this->n_moves < 9) return false;
    return !is_win(player);
}

bool MemoryTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

MemoryTTT_UI::MemoryTTT_UI() : UI<char>("=== Memory Tic-Tac-Toe ===", 3) {
    cout << "Marks are hidden after placement. Remember where you played!\n\n";
}

Player<char>* MemoryTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER) {
        return new MemoryTTT_AI_Player(name, symbol);
    }
    return new Player<char>(name, symbol, type);
}

Move<char>* MemoryTTT_UI::get_move(Player<char>* player) {
    MemoryTTT_AI_Player* ai_player = dynamic_cast<MemoryTTT_AI_Player*>(player);
    if (ai_player) {
        return ai_player->get_best_move();
    }

    cout << player->get_name() << "'s turn (symbol: " << player->get_symbol() << ")\n";
    int x, y;
    cout << "Enter position (row col): ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}

void MemoryTTT_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\n";
    cout << "    0   1   2\n";
    cout << "  +---+---+---+\n";
    for (int i = 0; i < 3; i++) {
        cout << i << " | " << matrix[i][0] << " | " << matrix[i][1] << " | " << matrix[i][2] << " |\n";
        cout << "  +---+---+---+\n";
    }
    cout << "\n";
}

void MemoryTTT_UI::display_memory_board(MemoryTTT_Board* board) {
    display_board_matrix(board->get_display_board());
}

Player<char>** MemoryTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer (AI)" };

    string nameX = this->get_player_name("Player X");
    PlayerType typeX = this->get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = this->get_player_name("Player O");
    PlayerType typeO = this->get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}