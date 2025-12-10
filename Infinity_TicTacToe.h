/**
 * @file Infinity_TicTacToe.h
 * @brief Defines classes for Infinity Tic-Tac-Toe game variant.
 *
 * This file implements a unique Tic-Tac-Toe variant where each player
 * can only have 3 pieces on the board at a time. After placing the 4th
 * piece, the oldest piece is automatically removed, creating a dynamic
 * game state.
 *
 * @author Board Game Team
 * @date 2024
 */

#ifndef INFINITY_TICTACTOE_H
#define INFINITY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <queue>

using namespace std;

/**
 * @class Infinity_Board
 * @brief Represents an Infinity Tic-Tac-Toe board.
 *
 * A 3×3 board where each player can only maintain 3 pieces simultaneously.
 * When a player places their 4th piece, their oldest piece is automatically
 * removed, creating a constantly shifting game state. Players must achieve
 * three-in-a-row before their pieces disappear.
 *
 * Key features:
 * - Standard 3×3 grid
 * - Maximum 3 pieces per player at any time
 * - FIFO (First-In-First-Out) piece removal
 * - Game continues indefinitely until someone wins
 * - No draw condition (game always has a winner eventually)
 *
 * @see Board
 */
class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character representing empty cells

    /**
     * @brief Queue storing X player's move positions in chronological order.
     *
     * Stores pairs of (row, col) coordinates. Used to track and remove
     * the oldest move when player exceeds 3 pieces.
     */
    queue<pair<int, int>> player_x_moves;

    /**
     * @brief Queue storing O player's move positions in chronological order.
     *
     * Stores pairs of (row, col) coordinates. Used to track and remove
     * the oldest move when player exceeds 3 pieces.
     */
    queue<pair<int, int>> player_o_moves;

    int x_move_count = 0; ///< Total number of moves made by X player
    int o_move_count = 0; ///< Total number of moves made by O player

public:
    /**
     * @brief Constructs a 3×3 Infinity board.
     *
     * Initializes all cells as empty and sets up move tracking queues.
     */
    Infinity_Board();

    /**
     * @brief Updates board with a player's move.
     *
     * Places the piece at the specified position and adds it to the
     * player's move queue. If the player now has more than 3 pieces,
     * automatically removes their oldest piece from the board.
     *
     * Process:
     * 1. Validate position is empty and in bounds
     * 2. Place new piece
     * 3. Add position to player's queue
     * 4. If player has >3 pieces, remove oldest from board and queue
     *
     * @param move Pointer to Move object containing position and symbol
     * @return true if move valid and applied, false if position occupied/invalid
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has won with three in a row.
     *
     * Checks all possible winning combinations:
     * - 3 rows (horizontal)
     * - 3 columns (vertical)
     * - 2 diagonals
     *
     * @param player Pointer to player being checked
     * @return true if player has three matching symbols in a line, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player has lost.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (not used in this variant)
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks if game is a draw.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (no draws in Infinity mode)
     */
    bool is_draw(Player<char>*) override { return false; }

    /**
     * @brief Checks if game is over.
     *
     * Game ends only when a player achieves three in a row.
     *
     * @param player Pointer to player being checked
     * @return true if player has won, false otherwise
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class Infinity_UI
 * @brief User interface for Infinity Tic-Tac-Toe.
 *
 * Handles player setup, move input, and displays game-specific rules
 * about the 3-piece limit and automatic removal mechanics.
 *
 * @see UI
 */
class Infinity_UI : public UI<char> {
public:
    /**
     * @brief Constructs UI and displays game rules.
     *
     * Shows:
     * - 3-piece limit per player
     * - Automatic removal of oldest piece
     * - Win condition
     * - No draw possibility
     */
    Infinity_UI();

    /**
     * @brief Destructor.
     */
    ~Infinity_UI() {}

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
     * @brief Gets a move from a player.
     *
     * For human players:
     * - Prompts for row and column (0-2)
     * - Validates input
     *
     * For computer players:
     * - Randomly selects empty cell
     * - Displays chosen position
     *
     * @param player Pointer to player making move
     * @return Pointer to Move object with position and symbol
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif // INFINITY_TICTACTOE_H