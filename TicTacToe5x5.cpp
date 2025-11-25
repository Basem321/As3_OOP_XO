#include "TicTacToe5x5.h"
#include <iostream>

// --- Board Implementation --- //

TicTacToe5x5::TicTacToe5x5() : Board<char>(5, 5) {
    n_moves = 0; 
}


bool TicTacToe5x5::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();

    
    if (x < 0 || x >= 5 || y < 0 || y >= 5 || board[x][y] != 0) {
        return false;
    }

   
    board[x][y] = move->get_symbol();
    n_moves++;

    return true;
}


int TicTacToe5x5::count_three_in_a_row(char symbol) {
    int count = 0;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            
            if (j + 2 < 5 && board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol)
                count++;

           
            if (i + 2 < 5 && board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol)
                count++;

            
            if (i + 2 < 5 && j + 2 < 5 && board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol)
                count++;

            if (i + 2 < 5 && j - 2 >= 0 && board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol)
                count++;
        }
    }
    return count;
}


bool TicTacToe5x5::game_is_over(Player<char>* player) {
    return n_moves >= 24;
}


bool TicTacToe5x5::is_win(Player<char>* player) {
    if (n_moves < 24) return false; 

    char my_symbol = player->get_symbol();
    char opp_symbol = (my_symbol == 'X') ? 'O' : 'X'; 

    int my_score = count_three_in_a_row(my_symbol);
    int opp_score = count_three_in_a_row(opp_symbol);

    return my_score > opp_score;
}

bool TicTacToe5x5::is_lose(Player<char>* player) {
    if (n_moves < 24) return false;

    char my_symbol = player->get_symbol();
    char opp_symbol = (my_symbol == 'X') ? 'O' : 'X';

    return count_three_in_a_row(my_symbol) < count_three_in_a_row(opp_symbol);
}

bool TicTacToe5x5::is_draw(Player<char>* player) {
    if (n_moves < 24) return false;

    char my_symbol = player->get_symbol();
    char opp_symbol = (my_symbol == 'X') ? 'O' : 'X';

    return count_three_in_a_row(my_symbol) == count_three_in_a_row(opp_symbol);
}


// --- UI Implementation --- //

TicTacToe5x5_UI::TicTacToe5x5_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe Game!", 5) {}

Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe5x5_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter move (row col): ";
        cin >> x >> y;
    }
    else {
        
        TicTacToe5x5* board = (TicTacToe5x5*)player->get_board_ptr();
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (board->get_board_matrix()[x][y] != 0); 
    }
    return new Move<char>(x, y, player->get_symbol());
}