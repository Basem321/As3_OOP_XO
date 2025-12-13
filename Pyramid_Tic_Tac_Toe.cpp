//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Pyramid_Tic_Tac_Toe.h"

using namespace std;

//--------------------------------------- Pyramid_Tic_Tac_Toe_Board Implementation

Pyramid_Tic_Tac_Toe_Board::Pyramid_Tic_Tac_Toe_Board() : Board(3, 5) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    // Mark the unused cells with 
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            if (((i == 0) && (j != 2)) || ((i == 1) && (j == 0 || j == 4))) {
                board[i][j] = '?';
            }
        }
    }
}

bool Pyramid_Tic_Tac_Toe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0 )) {

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

bool Pyramid_Tic_Tac_Toe_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

	//cheak the seven winning combinations
    if (all_equal(board[0][2], board[1][2], board[2][2]) && board[0][2]==sym) //vertical middle
		return true;
	if (all_equal(board[2][0], board[2][1], board[2][2]) && board[2][0] == sym) //bottom left horizontal
		return true;
	if (all_equal(board[2][2], board[2][3], board[2][4]) && board[2][2] == sym) //bottom right horizontal
		return true;
	if (all_equal(board[0][2], board[1][1], board[2][0]) && board[0][2] == sym) //left diagonal
		return true;
	if (all_equal(board[0][2], board[1][3], board[2][4]) && board[0][2] == sym) //right diagonal
		return true;
	if (all_equal(board[1][1], board[1][2], board[1][3]) && board[1][1] == sym) //middle left diagonal
		return true;
	if (all_equal(board[2][1], board[2][2], board[2][3]) && board[2][1] == sym) //middle right diagonal
		return true;
    return false;
}

bool Pyramid_Tic_Tac_Toe_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Pyramid_Tic_Tac_Toe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- Pyramid_Tic_Tac_Toe_UI Implementation

Pyramid_Tic_Tac_Toe_UI::Pyramid_Tic_Tac_Toe_UI() : UI<char>("Weclome to Pyramid_Tic_Tac_Toe Game ya ghaly", 3) {}

Player<char>* Pyramid_Tic_Tac_Toe_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Pyramid_Tic_Tac_Toe_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move coordinates : ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
