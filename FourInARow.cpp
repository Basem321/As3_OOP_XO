#include "FourInARow.h"
#include <iostream>
#include <cctype>

using namespace std;

FourInARow_Board::FourInARow_Board() : Board<char>(6, 7) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}

int FourInARow_Board::find_lowest_row(int col) {
    if (col < 0 || col >= columns) {
        return -1;
    }

    for (int row = rows - 1; row >= 0; row--) {
        if (board[row][col] == blank_symbol) {
            return row;
        }
    }

    return -1;
}

bool FourInARow_Board::update_board(Move<char>* move) {
    int col = move->get_y();
    char mark = toupper(move->get_symbol());

    int row = find_lowest_row(col);

    if (row == -1) {
        cout << "Column " << col << " is full! Try another column." << endl;
        return false;
    }

    board[row][col] = mark;
    n_moves++;

    return true;
}

bool FourInARow_Board::is_win(Player<char>* player) {
    const char sym = toupper(player->get_symbol());

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c <= columns - 4; c++) {
            if (board[r][c] == sym &&
                board[r][c + 1] == sym &&
                board[r][c + 2] == sym &&
                board[r][c + 3] == sym) {
                return true;
            }
        }
    }

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r <= rows - 4; r++) {
            if (board[r][c] == sym &&
                board[r + 1][c] == sym &&
                board[r + 2][c] == sym &&
                board[r + 3][c] == sym) {
                return true;
            }
        }
    }

    for (int r = 0; r <= rows - 4; r++) {
        for (int c = 0; c <= columns - 4; c++) {
            if (board[r][c] == sym &&
                board[r + 1][c + 1] == sym &&
                board[r + 2][c + 2] == sym &&
                board[r + 3][c + 3] == sym) {
                return true;
            }
        }
    }

    for (int r = 0; r <= rows - 4; r++) {
        for (int c = 3; c < columns; c++) {
            if (board[r][c] == sym &&
                board[r + 1][c - 1] == sym &&
                board[r + 2][c - 2] == sym &&
                board[r + 3][c - 3] == sym) {
                return true;
            }
        }
    }

    return false;
}

bool FourInARow_Board::is_draw(Player<char>* player) {
    return (n_moves >= rows * columns && !is_win(player));
}

bool FourInARow_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

FourInARow_UI::FourInARow_UI()
    : UI<char>("Welcome to FCAI Four-in-a-Row (Connect Four) Game!", 3) {
    cout << "\n=== This is Basem's game ===" << endl;
    cout << "\n=== Game Rules ===" << endl;
    cout << "- This is a 6x7 grid game" << endl;
    cout << "- Players take turns choosing a column (0-6)" << endl;
    cout << "- Your piece falls to the lowest available position in that column" << endl;
    cout << "- First player to get 4 in a row (horizontal, vertical, or diagonal) wins!" << endl;
    cout << "- The game is a draw if the board fills up with no winner\n" << endl;
}

Player<char>* FourInARow_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* FourInARow_UI::get_move(Player<char>* player) {
    int col;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol()
            << "), enter column number (0-6): ";

        cin >> col;

        while (cin.fail() || col < 0 || col >= 7) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid! Enter a column number between 0-6: ";
            cin >> col;
        }

        cin.ignore(1000, '\n');
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        FourInARow_Board* board = dynamic_cast<FourInARow_Board*>(player->get_board_ptr());

        int attempts = 0;
        do {
            col = rand() % 7;
            attempts++;
            if (attempts > 50) {
                for (int c = 0; c < 7; c++) {
                    if (board->get_board_matrix()[5][c] == '.') {
                        col = c;
                        break;
                    }
                }
                break;
            }
        } while (board->get_board_matrix()[5][col] != '.');

        cout << "\nComputer " << player->get_name() << " chooses column " << col << endl;
    }

    return new Move<char>(0, col, player->get_symbol());
}