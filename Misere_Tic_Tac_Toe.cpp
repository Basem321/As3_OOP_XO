#include <iostream>
#include <iomanip>
#include <cctype>  
#include "Misere_Tic_Tac_Toe.h"

using namespace std;



Misere_Tic_Tac_Toe_Board::Misere_Tic_Tac_Toe_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Misere_Tic_Tac_Toe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

bool Misere_Tic_Tac_Toe_Board::is_lose(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return (a == b && b == c && a == sym);
        };

    for (int i = 0; i < 3; ++i) {
        if (all_equal(board[i][0], board[i][1], board[i][2])) return true;
        if (all_equal(board[0][i], board[1][i], board[2][i])) return true;
    }

    if (all_equal(board[0][0], board[1][1], board[2][2])) return true;
    if (all_equal(board[0][2], board[1][1], board[2][0])) return true;

    return false;
}

bool Misere_Tic_Tac_Toe_Board::is_draw(Player<char>* player) {
    return false;
}

bool Misere_Tic_Tac_Toe_Board::is_win(Player<char>* player) {
    return (n_moves == 9 && !is_lose(player));
}

bool Misere_Tic_Tac_Toe_Board::game_is_over(Player<char>* player) {
    return is_lose(player) || is_win(player);
}



Misere_Tic_Tac_Toe_UI::Misere_Tic_Tac_Toe_UI() : UI<char>("Weclome to FCAI Misere Tic Tac Toe Game by Dr El-Ramly", 3) {}

Player<char>* Misere_Tic_Tac_Toe_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Misere_Tic_Tac_Toe_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}