/**
 * @file UltimateTicTacToe.h
 * @brief Defines classes for Ultimate Tic-Tac-Toe game.
 *
 * This file implements Ultimate Tic-Tac-Toe, a complex variant where
 * players play on 9 small Tic-Tac-Toe boards arranged in a 3×3 grid.
 * Winning a small board claims that position on the main board, and
 * the goal is to win three positions in a row on the main board.
 *
 * @author Board Game Team
 * @date 2024
 */

#ifndef ULTIMATE_TICTACTOE_H
#define ULTIMATE_TICTACTOE_H

#include "BoardGame_Classes.h"

 /**
  * @class MiniBoard
  * @brief Represents one 3×3 sub-board in Ultimate Tic-Tac-Toe.
  *
  * A standard Tic-Tac-Toe board that functions as one cell in the
  * larger 3×3 meta-game. When won, this mini-board's result is
  * recorded on the main board.
  *
  * Possible states:
  * - In progress: Empty or partially filled
  * - Won by X: Returns 'X' from check_winner()
  * - Won by O: Returns 'O' from check_winner()
  * - Draw: Returns 'D' from check_winner()
  *
  * @see Board
  */
class MiniBoard : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character representing empty cells

public:
    /**
     * @brief Constructs a 3×3 mini-board.
     */
    MiniBoard();

    /**
     * @brief Updates the mini-board with a move.
     *
     * @param move Pointer to Move with position and symbol
     * @return true if move valid and placed, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has won this mini-board.
     *
     * @param player Pointer to player being checked
     * @return true if player has three in a row, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player has lost this mini-board.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (handled by check_winner)
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks if mini-board is a draw.
     *
     * @param player Pointer to player being checked
     * @return true if board full with no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if mini-board game is complete.
     *
     * @param player Pointer to player being checked
     * @return true if won or drawn, false if still in progress
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Resets mini-board to empty state.
     *
     * Clears all cells and resets move counter. Used when
     * starting a new sub-game.
     */
    void reset();

    /**
     * @brief Determines the winner or draw state.
     *
     * @return 'X' if X won, 'O' if O won, 'D' if draw, 0 if in progress
     */
    char check_winner();
};

/**
 * @class UltimateTicTacToe_Board
 * @brief Represents the Ultimate Tic-Tac-Toe meta-board.
 *
 * Manages:
 * - A 3×3 grid of mini-board states (main_board)
 * - Two MiniBoard instances for actual gameplay
 * - Game flow logic (which board is active)
 * - Win condition for the overall game
 *
 * Game flow:
 * 1. Player selects which 3×3 position to play in
 * 2. Plays a complete Tic-Tac-Toe game on that mini-board
 * 3. Mini-board result is recorded on main_board
 * 4. Next player must play in position determined by previous move
 * 5. First player to win 3 main-board positions in a row wins
 *
 * Strategic depth:
 * - Your move position determines opponent's board
 * - Must balance winning current board vs forcing opponent to bad position
 * - Closed boards force choice of new board
 *
 * @see Board
 */
class UltimateTicTacToe_Board : public Board<char> {
private:
    MiniBoard mini_board_X; ///< Mini-board used when X player is active
    MiniBoard mini_board_O; ///< Mini-board used when O player is active
    char main_board[3][3];  ///< Tracks which positions are won (X/O/D) or open (0)

    int active_board_x;     ///< Row of currently active mini-board (-1 = any)
    int active_board_y;     ///< Column of currently active mini-board (-1 = any)
    bool first_move;        ///< True if no moves made yet
    Player<char>* current_player; ///< Player currently playing mini-board
    bool sub_game_in_progress;    ///< True when mini-board game is active

    int last_cell_x;        ///< Row of last move in mini-board
    int last_cell_y;        ///< Column of last move in mini-board

    /**
     * @brief Checks for three in a row on the main board.
     *
     * @param symbol Symbol to check for ('X' or 'O')
     * @return true if symbol has 3 in a row on main board, false otherwise
     */
    bool check_main_board_win(char symbol);

    /**
     * @brief Checks if main board is completely filled.
     *
     * @return true if all 9 positions won or drawn, false otherwise
     */
    bool is_main_board_full();

public:
    /**
     * @brief Constructs the Ultimate Tic-Tac-Toe board.
     *
     * Initializes main board to all zeros (empty) and sets
     * initial game state.
     */
    UltimateTicTacToe_Board();

    /**
     * @brief Updates the active mini-board with a move.
     *
     * Routes move to appropriate mini-board (X or O) and checks
     * if mini-board is complete. If complete, records result on
     * main board.
     *
     * @param move Pointer to Move for mini-board position
     * @return true if move valid, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player won main board.
     *
     * @param player Pointer to player being checked
     * @return true if player has 3 in a row on main board, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player lost main board.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (handled by is_win)
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks if overall game is a draw.
     *
     * Draw occurs when main board is full but no player has
     * three in a row.
     *
     * @param player Pointer to player being checked
     * @return true if main board full with no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if overall game is complete.
     *
     * @param player Pointer to player being checked
     * @return true if main board won or drawn, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Initiates a sub-game on specific board position.
     *
     * Sets up mini-board for play at specified main board position.
     *
     * @param board_x Row on main board (0-2)
     * @param board_y Column on main board (0-2)
     * @param player Pointer to player starting the sub-game
     */
    void start_sub_game(int board_x, int board_y, Player<char>* player);

    /**
     * @brief Ends current sub-game and updates active board.
     *
     * Called when mini-board is won/drawn. Determines next
     * active board based on last move position.
     */
    void end_sub_game();

    /**
     * @brief Gets the currently active mini-board.
     *
     * @return Pointer to MiniBoard (X's or O's), or nullptr if none active
     */
    MiniBoard* get_current_mini_board();

    /**
     * @brief Gets active board row.
     * @return Row index, or -1 if player can choose any board
     */
    int get_active_board_x() const { return active_board_x; }

    /**
     * @brief Gets active board column.
     * @return Column index, or -1 if player can choose any board
     */
    int get_active_board_y() const { return active_board_y; }

    /**
     * @brief Checks if this is the first move of the game.
     * @return true if no moves made yet, false otherwise
     */
    bool is_first_move() const { return first_move; }

    /**
     * @brief Checks if a sub-game is currently active.
     * @return true if playing on mini-board, false otherwise
     */
    bool is_sub_game_in_progress() const { return sub_game_in_progress; }

    /**
     * @brief Gets state of main board cell.
     * @param x Row (0-2)
     * @param y Column (0-2)
     * @return 'X', 'O', 'D', or 0 (empty)
     */
    char get_main_board_cell(int x, int y) const { return main_board[x][y]; }

    /**
     * @brief Gets reference to main board cell.
     * @param x Row (0-2)
     * @param y Column (0-2)
     * @return Reference to cell value
     */
    char& get_main_board_cell_ref(int x, int y) { return main_board[x][y]; }

    /**
     * @brief Checks if main board position is available.
     * @param x Row (0-2)
     * @param y Column (0-2)
     * @return true if position not yet won/drawn, false otherwise
     */
    bool is_position_available(int x, int y) const { return main_board[x][y] == 0; }
};

/**
 * @class UltimateTicTacToe_UI
 * @brief User interface for Ultimate Tic-Tac-Toe.
 *
 * Provides:
 * - Game rules explanation
 * - Main board visualization
 * - Mini-board visualization
 * - Board selection input
 * - Move input within mini-boards
 *
 * @see UI
 */
class UltimateTicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructs UI and displays comprehensive rules.
     *
     * Explains:
     * - 9 small boards in 3×3 arrangement
     * - Sub-game mechanics
     * - Board selection rules
     * - Win condition
     */
    UltimateTicTacToe_UI();

    /**
     * @brief Creates a player of specified type.
     *
     * @param name Player name
     * @param symbol Player symbol ('X' or 'O')
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to new Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a complete move including board selection.
     *
     * Process:
     * 1. If no active board, prompt for board selection
     * 2. Display main board and selected mini-board
     * 3. Prompt for move within mini-board
     *
     * @param player Pointer to player making move
     * @return Pointer to Move for mini-board position
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the 3×3 main board state.
     *
     * Shows which positions are won by X, O, drawn, or still open.
     *
     * @param board Pointer to UltimateTicTacToe_Board
     */
    void display_main_board(UltimateTicTacToe_Board* board);

    /**
     * @brief Displays the current mini-board being played.
     *
     * Shows 3×3 grid with current pieces placed.
     *
     * @param mini_board Pointer to MiniBoard
     * @param board_x Main board row of this mini-board
     * @param board_y Main board column of this mini-board
     */
    void display_mini_board(MiniBoard* mini_board, int board_x, int board_y);
};

#endif // ULTIMATE_TICTACTOE_H