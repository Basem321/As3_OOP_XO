//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Tic_Tac_Toe_4x4.h"
#include <cstdlib>

using namespace std;

//--------------------------------------- Tic_Tac_Toe_4x4_Board Implementation

Tic_Tac_Toe_4x4_Board::Tic_Tac_Toe_4x4_Board() : Board(4, 4) {
    // Initialize all cells with blank_symbol
    for (auto& row : board) {
        for (auto& cell : row){
            cell = blank_symbol;}
    }
    for (int i=0;i<=3;i+=3){
        for (int j = 0; j <= 3; j++) {
            if ((i + j) % 2 == 0) {
				board[i][j] = 'O';
            }
            else
            {
                board[i][j] = 'X';

            }
    }
    
    }
}




bool Tic_Tac_Toe_4x4_Board::update_board(Move<char>* move) {
    int oldx = move[0].get_x();
    int newx = move[1].get_x();
    int oldy = move[0].get_y();
    int newy = move[1].get_y();
    char mark = move[1].get_symbol();
    
    // Validate move and apply if valid
    if (!(newx < 0 || newx >= rows || newy < 0 || newy >= columns) &&
        (board[newx][newy] == blank_symbol) && (((newy == oldy) && (abs(newx - oldx) == 1)) || ((newx == oldx) && (abs(oldy - newy == 1)))) && (board[oldx][oldy]==mark)) {

		board[oldx][oldy] = blank_symbol;
		board[newx][newy] = mark;
        
        
        return true;
    }
    return false;
}

bool Tic_Tac_Toe_4x4_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; i++) {
        if((all_equal(board[i][0],board[i][1],board[i][2])&&board[i][0]==sym) || ( all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
    
			return true;
    }
    for (int i = 0; i < rows; i++) {
        if ((all_equal(board[i][1], board[i][2], board[i][3]) && board[i][1] == sym) || (all_equal(board[1][i], board[2][i], board[3][i]) && board[1][i] == sym)) 

                return true;
     }
    // Check diagonals
    for (int n = 0; n < 2; n++) {
        for (int j = 0; j < 2; j++) {
            if ((all_equal(board[0+j][0+n], board[1+j][1+n], board[2+j][2+n]) && board[1+j][1+n] == sym) ||
                (all_equal(board[0+j][2+n], board[1+j][1+n], board[2+j][0+n]) && board[1+j][1+n] == sym))
                return true;
        }
    }

    return false;
}

bool Tic_Tac_Toe_4x4_Board::is_draw(Player<char>* player) {
    return false;
}

bool Tic_Tac_Toe_4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player) ;
}

//--------------------------------------- Tic_Tac_Toe_4x4_UI Implementation

Tic_Tac_Toe_4x4_UI::Tic_Tac_Toe_4x4_UI() : UI<char>("Weclome to FCAI Tic_Tac_Toe_4x4 Game", 4) {}

Player<char>* Tic_Tac_Toe_4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Tic_Tac_Toe_4x4_UI::get_move(Player<char>* player) {
    int x1,y1,x2,y2;
  
    if (player->get_type() == PlayerType::HUMAN) {
       cout << player->get_name() <<"("<<player->get_symbol()<<")"  << "'s turn. Enter the coordinates of the piece to move (row and column): \n";
        cin >> x1 >> y1 ;
        cout << player->get_name() << "(" << player->get_symbol() << ")" << "'s turn. Enter the coordinates of the place to move (row and column):\n ";
		cin >> x2 >> y2;
  
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x1 = rand() % player->get_board_ptr()->get_rows();
        x2 = rand() % player->get_board_ptr()->get_rows();
        y1 = rand() % player->get_board_ptr()->get_columns();
        y2 = rand() % player->get_board_ptr()->get_columns();
    }
    Move<char>* moves = new Move<char>[2] { Move<char>(x1, y1, 0), Move<char>(x2, y2, player->get_symbol()) };
    return moves;
}