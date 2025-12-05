#include "Infinity_TicTacToe.h"
#include <iostream>
#include <cctype>

using namespace std;

Infinity_Board::Infinity_Board() : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Infinity_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = toupper(move->get_symbol());

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    if (board[x][y] != blank_symbol) {
        return false;
    }

    board[x][y] = mark;
    n_moves++;

    if (mark == 'X') {
        player_x_moves.push({ x, y });
        x_move_count++;

        if (x_move_count > 3) {
            auto oldest = player_x_moves.front();
            player_x_moves.pop();
            board[oldest.first][oldest.second] = blank_symbol;
            n_moves--;
        }
    }
    else if (mark == 'O') {
        player_o_moves.push({ x, y }); 
        o_move_count++;

        if (o_move_count > 3) {
            auto oldest = player_o_moves.front();
            player_o_moves.pop();
            board[oldest.first][oldest.second] = blank_symbol;
            n_moves--;
        }
    }

    return true;
}

bool Infinity_Board::is_win(Player<char>* player) {
    const char sym = toupper(player->get_symbol());

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a == sym;
        };

    for (int i = 0; i < rows; ++i) {
        if (all_equal(board[i][0], board[i][1], board[i][2]))
            return true;
    }

    for (int i = 0; i < columns; ++i) {
        if (all_equal(board[0][i], board[1][i], board[2][i]))
            return true;
    }

    if (all_equal(board[0][0], board[1][1], board[2][2]))
        return true;

    if (all_equal(board[0][2], board[1][1], board[2][0]))
        return true;

    return false;
}

bool Infinity_Board::game_is_over(Player<char>* player) {
    return is_win(player);
}

Infinity_UI::Infinity_UI()
    : UI<char>("Welcome to FCAI Infinity Tic-Tac-Toe Game!", 3) {
    cout << "\n=== Game Rules ===" << endl;
    cout << "- After every 3 moves per player, the oldest move is removed" << endl;
    cout << "- Win by aligning three marks in a row before they vanish" << endl;
    cout << "- The game continues until someone wins\n" << endl;
}

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Infinity_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol()
            << "), enter your move (row and column, 0-2): ";
        cin >> x >> y;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter row and column (0-2): ";
            cin >> x >> y;
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        do {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != '.');

        cout << "\nComputer " << player->get_name() << " plays at position ("
            << x << ", " << y << ")" << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}