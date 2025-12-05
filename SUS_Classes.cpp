#include "SUS_Classes.h"
#include <iostream>
#include <cctype>

using namespace std;

SUS_Board::SUS_Board() : Board<char>(3, 3), s_score(0), u_score(0) {
}

bool SUS_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = toupper(move->get_symbol());

    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != 0) {
        return false;
    }

    board[r][c] = symbol;
    n_moves++;

    int points = 0;

    auto isValid = [&](int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < columns;
        };

    if (symbol == 'S') {
 
        int dr[] = { 0, 0, 1, -1, 1, -1, 1, -1 };
        int dc[] = { 1, -1, 0, 0, 1, -1, -1, 1 };

        for (int i = 0; i < 8; ++i) {
            int r1 = r + dr[i]; 
            int c1 = c + dc[i];
            int r2 = r + dr[i] * 2;
            int c2 = c + dc[i] * 2;

            if (isValid(r1, c1) && isValid(r2, c2)) {
                if (board[r1][c1] == 'U' && board[r2][c2] == 'S') {
                    points++;
                }
            }
        }
    }
    else if (symbol == 'U') {


        if (isValid(r, c - 1) && isValid(r, c + 1) && board[r][c - 1] == 'S' && board[r][c + 1] == 'S') 
            points++;

        if (isValid(r - 1, c) && isValid(r + 1, c) && board[r - 1][c] == 'S' && board[r + 1][c] == 'S') 
            points++;

        if (isValid(r - 1, c - 1) && isValid(r + 1, c + 1) && board[r - 1][c - 1] == 'S' && board[r + 1][c + 1] == 'S') 
            points++;

        if (isValid(r - 1, c + 1) && isValid(r + 1, c - 1) && board[r - 1][c + 1] == 'S' && board[r + 1][c - 1] == 'S') 
            points++;
    }

    if (symbol == 'S') {
        s_score += points;
    }
    else {
        u_score += points;
    }

    return true;
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves >= 9;
}

bool SUS_Board::is_win(Player<char>* player) {
    if (!game_is_over(player)) return false;

    char sym = player->get_symbol();
    if (sym == 'S') return s_score > u_score;
    if (sym == 'U') return u_score > s_score;
    return false;
}

bool SUS_Board::is_lose(Player<char>* player) {
    if (!game_is_over(player)) return false;

    char sym = player->get_symbol();
    if (sym == 'S') return u_score > s_score;
    if (sym == 'U') return s_score > u_score;
    return false;
}

bool SUS_Board::is_draw(Player<char>* player) {
    if (!game_is_over(player)) return false;
    return s_score == u_score;
}


SUS_UI::SUS_UI() : UI<char>("Welcome to the SUS Game!", 3) {
}

Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cout << "\n-- Setup Player 1 (Plays 'S') --" << endl;
    string nameS = get_player_name("Player 1");
    PlayerType typeS = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(nameS, 'S', typeS);

    cout << "\n-- Setup Player 2 (Plays 'U') --" << endl;
    string nameU = get_player_name("Player 2");
    PlayerType typeU = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(nameU, 'U', typeU);

    return players;
}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    SUS_Board* board = dynamic_cast<SUS_Board*>(player->get_board_ptr());
    if (board) {
        cout << "\nCurrent Score -> S: " << board->get_s_score()
            << " | U: " << board->get_u_score() << endl;
    }

    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter row and column (0-2): ";
        cin >> x >> y;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter numbers: ";
            cin >> x >> y;
        }
    }
    else {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != 0);
        cout << "Computer " << player->get_name() << " places at " << x << " " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}