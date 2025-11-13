#include <iostream>
#include <algorithm>
#include "Numerical_tic_tac_9.h"
#include <cstdlib>
#include <ctime>
using namespace std;
Numerical_Board::Numerical_Board() : Board<int>(3, 3) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_value;
        }
    }

    Player_Odd  = {1, 3, 5, 7, 9};
    Player_Even = {2, 4, 6, 8};
}

bool Numerical_Board::is_valid_number(int number, Player<int>* player) {
    if (used_numbers.count(number) > 0) {
        return false;
    }

    int player_id = player->get_symbol(); 

    if (player_id == 1) {
        return Player_Odd.count(number) > 0;
    } else {
        return Player_Even.count(number) > 0;
    }
}

set<int> Numerical_Board::get_available_numbers(Player<int>* player) {
    int player_id = player->get_symbol();
    set<int> available;

    if (player_id == 1) {
        for (int num : Player_Odd) {
            if (used_numbers.count(num) == 0) {
                available.insert(num);
            }
        }
    } else {
        for (int num : Player_Even) {
            if (used_numbers.count(num) == 0) {
                available.insert(num);
            }
        }
    }

    return available;
}

bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    if (board[x][y] != blank_value) {
        return false;
    }

    if (num == 0) {
        n_moves--;
        board[x][y] = blank_value;
        return true;
    }

    if (used_numbers.count(num) > 0) {
        return false;
    }

    board[x][y] = num;
    used_numbers.insert(num);
    n_moves++;

    return true;
}

bool Numerical_Board::is_win(Player<int>* player) {
    for (int i = 0; i < rows; i++) {
        int sum = board[i][0] + board[i][1] + board[i][2];
        if (sum == 15 && board[i][0] != blank_value &&
            board[i][1] != blank_value && board[i][2] != blank_value) {
            return true;
        }
    }

    for (int j = 0; j < columns; j++) {
        int sum = board[0][j] + board[1][j] + board[2][j];
        if (sum == 15 && board[0][j] != blank_value &&
            board[1][j] != blank_value && board[2][j] != blank_value) {
            return true;
        }
    }

    int sum_diag1 = board[0][0] + board[1][1] + board[2][2];
    if (sum_diag1 == 15 && board[0][0] != blank_value &&
        board[1][1] != blank_value && board[2][2] != blank_value) {
        return true;
    }

    int sum_diag2 = board[0][2] + board[1][1] + board[2][0];
    if (sum_diag2 == 15 && board[0][2] != blank_value &&
        board[1][1] != blank_value && board[2][0] != blank_value) {
        return true;
    }

    return false;
}

bool Numerical_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

Numerical_UI::Numerical_UI()
    : UI<int>("Welcome to FCAI Numerical Tic-Tac-Toe Game!", 3) {
    cout << "\nGame Rules:\n";
    cout << "- Player 1 uses ODD numbers: 1, 3, 5, 7, 9\n";
    cout << "- Player 2 uses EVEN numbers: 2, 4, 6, 8\n";
    cout << "- Each number can only be used once\n";
    cout << "- Win by getting three numbers that sum to 15\n";
    cout << "  (in a row, column, or diagonal)\n\n";
}

Player<int>** Numerical_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = {"Human", "Computer"};

    string name1 = get_player_name("Player 1 (Odd numbers)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1);

    string name2 = get_player_name("Player 2 (Even numbers)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2); 

    return players;
}

Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (Uses "
         << (symbol == 1 ? "ODD" : "EVEN") << " numbers)\n";

    return new Player<int>(name, symbol, type);
}

Move<int>* Numerical_UI::get_move(Player<int>* player) {
    Numerical_Board* board = dynamic_cast<Numerical_Board*>(player->get_board_ptr());

    if (!board) {
        cerr << "Error: Invalid board type!\n";
        return nullptr;
    }

    int x, y, number;

    if (player->get_type() == PlayerType::HUMAN) {
        set<int> available = board->get_available_numbers(player);

        cout << "\n" << player->get_name() << "'s turn\n";
        cout << "Available numbers: ";
        for (int num : available) {
            cout << num << " ";
        }
        cout << endl;

        do {
            cout << "Enter the number you want to place: ";
            cin >> number;

            if (available.count(number) == 0) {
                cout << "Invalid number! Choose from available numbers.\n";
            }
        } while (available.count(number) == 0);

        cout << "Enter position (row and column, 0-2): ";
        cin >> x >> y;

    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        set<int> available = board->get_available_numbers(player);

        if (available.empty()) {
            return nullptr;
        }

        auto it = available.begin();
        advance(it, rand() % available.size());
        number = *it;

        do {
            x = rand() % board->get_rows();
            y = rand() % board->get_columns();
        } while (board->get_board_matrix()[x][y] != 0);

        cout << "\nComputer " << player->get_name() << " plays: "
             << number << " at position (" << x << ", " << y << ")\n";
    }

    return new Move<int>(x, y, number);
}