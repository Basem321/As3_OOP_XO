#include "UltimateTicTacToe.h"
#include <iostream>
#include <iomanip>

using namespace std;

MiniBoard::MiniBoard() : Board<char>(3, 3) {
    reset();
}

void MiniBoard::reset() {
    n_moves = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = blank_symbol;
        }
    }
}

bool MiniBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (board[x][y] != blank_symbol) return false;

    board[x][y] = symbol;
    n_moves++;
    return true;
}

char MiniBoard::check_winner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != blank_symbol &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] != blank_symbol &&
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j]) {
            return board[0][j];
        }
    }

    if (board[0][0] != blank_symbol &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != blank_symbol &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        return board[0][2];
    }

    if (n_moves >= 9) return 'D';

    return 0;
}

bool MiniBoard::is_win(Player<char>* player) {
    return check_winner() == player->get_symbol();
}

bool MiniBoard::is_draw(Player<char>* player) {
    return check_winner() == 'D';
}

bool MiniBoard::game_is_over(Player<char>* player) {
    char winner = check_winner();
    return winner != 0;
}

UltimateTicTacToe_Board::UltimateTicTacToe_Board()
    : Board<char>(3, 3), active_board_x(-1), active_board_y(-1),
    first_move(true), current_player(nullptr), sub_game_in_progress(false),
    last_cell_x(-1), last_cell_y(-1) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            main_board[i][j] = 0;
        }
    }
}

void UltimateTicTacToe_Board::start_sub_game(int board_x, int board_y, Player<char>* player) {
    active_board_x = board_x;
    active_board_y = board_y;
    current_player = player;
    sub_game_in_progress = true;

    if (player && player->get_symbol() == 'X') {
        mini_board_X.reset();
    }
    else if (player) {
        mini_board_O.reset();
    }
}

void UltimateTicTacToe_Board::end_sub_game() {
    sub_game_in_progress = false;
    if (is_position_available(last_cell_x, last_cell_y)) {
        active_board_x = last_cell_x;
        active_board_y = last_cell_y;
    }
    else {
        active_board_x = -1;
        active_board_y = -1;
    }
    current_player = nullptr;
}

MiniBoard* UltimateTicTacToe_Board::get_current_mini_board() {
    if (!current_player) return nullptr;

    if (current_player->get_symbol() == 'X') {
        return &mini_board_X;
    }
    else {
        return &mini_board_O;
    }
}

bool UltimateTicTacToe_Board::update_board(Move<char>* move) {
    if (sub_game_in_progress) {
        MiniBoard* mini = get_current_mini_board();
        if (mini && mini->update_board(move)) {
            last_cell_x = move->get_x();
            last_cell_y = move->get_y();

            if (mini->game_is_over(current_player)) {
                char winner = mini->check_winner();
                if (winner == 'D') {
                    main_board[active_board_x][active_board_y] = 'D';
                }
                else {
                    main_board[active_board_x][active_board_y] = winner;
                }
                end_sub_game();
            }
            return true;
        }
        return false;
    }
    return true;
}

bool UltimateTicTacToe_Board::check_main_board_win(char symbol) {
    for (int i = 0; i < 3; i++) {
        if (main_board[i][0] == symbol &&
            main_board[i][1] == symbol &&
            main_board[i][2] == symbol) {
            return true;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (main_board[0][j] == symbol &&
            main_board[1][j] == symbol &&
            main_board[2][j] == symbol) {
            return true;
        }
    }

    if (main_board[0][0] == symbol &&
        main_board[1][1] == symbol &&
        main_board[2][2] == symbol) {
        return true;
    }
    if (main_board[0][2] == symbol &&
        main_board[1][1] == symbol &&
        main_board[2][0] == symbol) {
        return true;
    }

    return false;
}

bool UltimateTicTacToe_Board::is_main_board_full() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (main_board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool UltimateTicTacToe_Board::is_win(Player<char>* player) {
    return check_main_board_win(player->get_symbol());
}

bool UltimateTicTacToe_Board::is_draw(Player<char>* player) {
    if (is_win(player)) return false;
    return is_main_board_full();
}

bool UltimateTicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

UltimateTicTacToe_UI::UltimateTicTacToe_UI()
    : UI<char>("Welcome to Ultimate Tic-Tac-Toe!", 3) {
    cout << "\n=== ULTIMATE TIC-TAC-TOE RULES ===\n";
    cout << "1. The game consists of 9 small 3x3 boards arranged in a 3x3 grid\n";
    cout << "2. Each turn, you first choose which board to play on (if available)\n";
    cout << "3. Then play a normal 3x3 Tic-Tac-Toe game on that board\n";
    cout << "4. Win the small board, and you claim that position on the main board\n";
    cout << "5. The position you win determines where your opponent plays next\n";
    cout << "6. Win the game by winning 3 positions in a row on the main board!\n\n";
}

Player<char>* UltimateTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

void UltimateTicTacToe_UI::display_main_board(UltimateTicTacToe_Board* board) {
    system("cls");

    cout << "\n=== MAIN BOARD STATUS ===\n";
    cout << "   0   1   2\n";
    cout << " +---+---+---+\n";
    for (int i = 0; i < 3; i++) {
        cout << i << "|";
        for (int j = 0; j < 3; j++) {
            char cell = board->get_main_board_cell(i, j);
            if (cell == 0) {
                cout << "   ";
            }
            else if (cell == 'D') {
                cout << " - ";
            }
            else {
                cout << " " << cell << " ";
            }
            cout << "|";
        }
        cout << "\n +---+---+---+\n";
    }
    cout << endl;
}

void UltimateTicTacToe_UI::display_mini_board(MiniBoard* mini_board, int board_x, int board_y) {
    cout << "\n=== Playing on Board Position (" << board_x << ", " << board_y << ") ===\n";
    cout << "   0   1   2\n";
    cout << " +---+---+---+\n";

    auto matrix = mini_board->get_board_matrix();
    for (int i = 0; i < 3; i++) {
        cout << i << "|";
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == '.') {
                cout << "   ";
            }
            else {
                cout << " " << matrix[i][j] << " ";
            }
            cout << "|";
        }
        cout << "\n +---+---+---+\n";
    }
    cout << endl;
}

Move<char>* UltimateTicTacToe_UI::get_move(Player<char>* player) {
    UltimateTicTacToe_Board* ult_board = dynamic_cast<UltimateTicTacToe_Board*>(player->get_board_ptr());

    if (!ult_board) {
        cerr << "Error: Invalid board type!\n";
        return nullptr;
    }

    if (!ult_board->is_sub_game_in_progress()) {
        int board_x = ult_board->get_active_board_x();
        int board_y = ult_board->get_active_board_y();

        if (board_x == -1 || !ult_board->is_position_available(board_x, board_y)) {
            display_main_board(ult_board);

            if (player->get_type() == PlayerType::HUMAN) {
                cout << player->get_name() << " (" << player->get_symbol() << "), choose a board position:\n";

                cout << "Available positions: ";
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (ult_board->is_position_available(i, j)) {
                            cout << "(" << i << "," << j << ") ";
                        }
                    }
                }
                cout << endl;

                do {
                    cout << "Enter board row (0-2): ";
                    cin >> board_x;
                    cout << "Enter board column (0-2): ";
                    cin >> board_y;

                    if (!ult_board->is_position_available(board_x, board_y)) {
                        cout << "That position is already won! Choose another.\n";
                    }
                } while (!ult_board->is_position_available(board_x, board_y));
            }
            else {
                do {
                    board_x = rand() % 3;
                    board_y = rand() % 3;
                } while (!ult_board->is_position_available(board_x, board_y));

                cout << "Computer " << player->get_name() << " chooses board ("
                    << board_x << ", " << board_y << ")\n";
                system("pause");
            }
        }

        ult_board->start_sub_game(board_x, board_y, player);
    }

    MiniBoard* mini_board = ult_board->get_current_mini_board();

    if (!mini_board) {
        cerr << "Error: No active mini board!\n";
        return new Move<char>(0, 0, player->get_symbol());
    }

    int board_x = ult_board->get_active_board_x();
    int board_y = ult_board->get_active_board_y();

    display_main_board(ult_board);
    display_mini_board(mini_board, board_x, board_y);

    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), make your move:\n";
        cout << "Enter row (0-2): ";
        cin >> x;
        cout << "Enter column (0-2): ";
        cin >> y;
    }
    else {
        auto matrix = mini_board->get_board_matrix();
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (matrix[x][y] != '.');

        cout << "Computer plays at (" << x << ", " << y << ")\n";
        system("pause");
    }

    return new Move<char>(x, y, player->get_symbol());
}