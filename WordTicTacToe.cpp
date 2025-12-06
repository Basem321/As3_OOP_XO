#include "WordTicTacToe.h"
#include <iostream>
#include <algorithm>
#include <cctype>   


// WordTicTacToe_Board Implementation


WordTicTacToe_Board::WordTicTacToe_Board() : Board<char>(3, 3) {
    
    load_dic("dic.txt");
}

void WordTicTacToe_Board::load_dic(const string& filename)
{
 
    ifstream file(filename);
    string word;

    if (!file.is_open()) {
        cout << "Error: Could not open dictionary file '" << filename << "'.\n";
        cout << "Please ensure 'dic.txt' is in the project directory.\n";
        return;
    }

    while (file >> word) {
       
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        dic.insert(word);
    }
    file.close();
    cout << "Dictionary loaded successfully (" << dic.size() << " words).\n";
}


bool WordTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = toupper(move->get_symbol());

   
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol)) {

        n_moves++;
        board[x][y] = mark;
        return true;
    }
    return false;
}


bool WordTicTacToe_Board::is_win(Player<char>* player) {
   
    if (n_moves < 3) return false;

    for (int i = 0; i < rows; ++i) {
        if (board[i][0] != blank_symbol && board[i][1] != blank_symbol && board[i][2] != blank_symbol) {
            string word = "";
            word += board[i][0];
            word += board[i][1];
            word += board[i][2];
            if (dic.count(word)) return true;
        }
    }

   
    for (int j = 0; j < columns; ++j) {
        if (board[0][j] != blank_symbol && board[1][j] != blank_symbol && board[2][j] != blank_symbol) {
            string word = "";
            word += board[0][j];
            word += board[1][j];
            word += board[2][j];
            if (dic.count(word)) return true;
        }
    }

    
    if (board[0][0] != blank_symbol && board[1][1] != blank_symbol && board[2][2] != blank_symbol) {
        string word = "";
        word += board[0][0];
        word += board[1][1];
        word += board[2][2];
        if (dic.count(word)) return true;
    }

    
    if (board[0][2] != blank_symbol && board[1][1] != blank_symbol && board[2][0] != blank_symbol) {
        string word = "";
        word += board[0][2];
        word += board[1][1];
        word += board[2][0];
        if (dic.count(word)) return true;
    }

    return false;
}

bool WordTicTacToe_Board::is_draw(Player<char>* player) {
   
    return (n_moves == 9 && !is_win(player));
}

bool WordTicTacToe_Board::game_is_over(Player<char>* player) {
   
    return is_win(player) || (n_moves == 9);
}


// WordTicTacToe_UI Implementation

WordTicTacToe_UI::WordTicTacToe_UI() : UI<char>("Welcome to Word Tic-Tac-Toe Game!", 3) {}


Player<char>* WordTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* WordTicTacToe_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << " turn), enter letter: ";
        cin >> letter;
        
        while (cin.fail() || !isalpha(letter)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a single letter: ";
            cin >> letter;
        }

        cout << "Enter position (row col 0-2): ";
        cin >> x >> y;
        
        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter row and column (0-2): ";
            cin >> x >> y;
        }
    }
    else { 
        
        letter = 'A' + (rand() % 26);

        
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != 0);

        cout << "Computer " << player->get_name() << " places '" << letter
            << "' at (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, letter);
}


Player<char>** WordTicTacToe_UI::setup_players() {
    cout << "\nPlayers will place letters to form a 3-letter word.\n";
    return UI<char>::setup_players();
}