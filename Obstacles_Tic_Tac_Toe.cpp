#include "Obstacles_Tic_Tac_Toe.h"

Obstacles_Tic_Tac_Toe_Board::Obstacles_Tic_Tac_Toe_Board()
    : Board<char>(ROWS, COLS)
{

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            board[r][c] = '.';

    srand(static_cast<unsigned int>(time(nullptr)));
	
}

void Obstacles_Tic_Tac_Toe_Board::clear_board() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            board[r][c] = '.';
    n_moves = 0;
}

vector<pair<int, int>> Obstacles_Tic_Tac_Toe_Board::get_empty_cells() const {
    vector<pair<int, int>> empties;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            if (board[r][c] == '.')
                empties.emplace_back(r, c);
    return empties;
}

void Obstacles_Tic_Tac_Toe_Board::add_random_obstacles(int n) {
    auto empties = get_empty_cells();
    if (empties.empty()) return;

    static std::mt19937 rng(static_cast<unsigned int>(std::random_device{}()));
    std::shuffle(empties.begin(), empties.end(), rng);

    int placed = 0;
    for (auto& p : empties) {
        if (placed >= n) break;
        int r = p.first, c = p.second;
        board[r][c] = '#';
        ++placed;
    }
}

bool Obstacles_Tic_Tac_Toe_Board::update_board(Move<char>* move) {
    if (!move) return false;
    int r = move->get_x();
    int c = move->get_y();
    char sym = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns) return false;
    if (board[r][c] != '.') return false;
    board[r][c] = sym;
    ++n_moves;
	++moves_this_round;

    if (moves_this_round == 2) {
		add_random_obstacles(1);
		moves_this_round = 0;
    }
    return true;
}

bool Obstacles_Tic_Tac_Toe_Board::four_in_a_row_from(int r, int c, char sym) const {
    if (board[r][c] != sym) return false;
    const int dirs[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
    for (int d = 0; d < 4; ++d) {
        int dr = dirs[d][0], dc = dirs[d][1];
        int cnt = 1;
        int rr = r + dr, cc = c + dc;
        while (rr >= 0 && rr < rows && cc >= 0 && cc < columns && board[rr][cc] == sym) {
            ++cnt; rr += dr; cc += dc;
        }
        rr = r - dr; cc = c - dc;
        while (rr >= 0 && rr < rows && cc >= 0 && cc < columns && board[rr][cc] == sym) {
            ++cnt; rr -= dr; cc -= dc;
        }
        if (cnt >= 4) return true;
    }
    return false;
}

bool Obstacles_Tic_Tac_Toe_Board::board_full() const {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            if (board[r][c] == '.') return false;
    return true;
}

bool Obstacles_Tic_Tac_Toe_Board::is_win(Player<char>* player) {
    if (!player) return false;
    char sym = player->get_symbol();
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c) {
            if (board[r][c] == sym && four_in_a_row_from(r, c, sym))
                return true;
        }
    return false;
}

bool Obstacles_Tic_Tac_Toe_Board::is_lose(Player<char>* player) {
    if (!player) return false;

    char sym = player->get_symbol();
    char other = (sym == 'X') ? 'O' : 'X';
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c) {
            if (board[r][c] == other && four_in_a_row_from(r, c, other))
                return true;
        }
    return false;
}

bool Obstacles_Tic_Tac_Toe_Board::is_draw(Player<char>* player) {

    if (board_full()) {

        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c) {
                char ch = board[r][c];
                if (ch == 'X' || ch == 'O')
                    if (four_in_a_row_from(r, c, ch)) return false;
            }
        return true;
    }
    return false;
}

bool Obstacles_Tic_Tac_Toe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}


Move<char>* Obstacles_Tic_Tac_Toe_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 5): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* Obstacles_Tic_Tac_Toe_UI::create_player(string& name, char symbol, PlayerType type) {
    Player<char>* p = new Player<char>(name, symbol, type);
    return p;
}