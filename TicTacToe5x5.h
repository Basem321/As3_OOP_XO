/**
 * @file TicTacToe5x5.h
 * @brief Defines classes for 5×5 Tic-Tac-Toe game variant.
 *
 * This file implements an expanded Tic-Tac-Toe game on a 5×5 grid where
 * players compete to create the most three-in-a-row patterns. After
 * 24 moves (filling almost the entire board), the player with more
 * three-in-a-row sequences wins.
 *
 * @author Board Game Team
 * @date 2024
 */

#pragma once

#include "BoardGame_Classes.h"

 /**
  * @class TicTacToe5x5
  * @brief Represents a 5×5 Tic-Tac-Toe board with counting victory.
  *
  * Unlike traditional Tic-Tac-Toe, this variant:
  * - Uses a 5×5 grid (25 cells total)
  * - Game runs for exactly 24 moves (leaving 1 empty cell)
  * - Players can create multiple three-in-a-row patterns
  * - Winner is determined by counting total three-in-a-rows
  *
  * Counting rules:
  * - Each unique sequence of 3 matching symbols counts as 1 point
  * - Sequences checked in all directions: →, ↓, ↘, ↙
  * - Overlapping patterns both count (e.g., XXXX has 2 patterns)
  *
  * Example scoring:
  * @code
  * X X X . .   ← This row has 1 three-in-a-row
  * X X X X .   ← This row has 2 three-in-a-rows (positions 0-2 and 1-3)
  * @endcode
  *
  * Game phases:
  * 1. Placement phase: Players alternate placing pieces (moves 1-24)
  * 2. Scoring phase: Count all three-in-a-rows for each player
  * 3. Victory: Player with more patterns wins
  *
  * @see Board
  */
class TicTacToe5x5 : public Board<char> {
public:
    /**
     * @brief Constructs a 5×5 board.
     *
     * Initializes empty 5×5 grid with move counter at 0.
     */
    TicTacToe5x5();

    /**
     * @brief Updates board with a player's move.
     *
     * Validates position is in bounds (0-4, 0-4) and empty
     * before placing the piece.
     *
     * @param move Pointer to Move with position and symbol
     * @return true if move valid and placed, false if position invalid/occupied
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has won (more three-in-a-rows).
     *
     * Only evaluated after 24 moves. Counts all three-in-a-row
     * patterns for both players and compares.
     *
     * @param player Pointer to player being checked
     * @return true if 24 moves done and player has more patterns, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player has lost (fewer three-in-a-rows).
     *
     * Only evaluated after 24 moves.
     *
     * @param player Pointer to player being checked
     * @return true if 24 moves done and player has fewer patterns, false otherwise
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if game is a draw (equal three-in-a-rows).
     *
     * Only evaluated after 24 moves.
     *
     * @param player Pointer to player being checked
     * @return true if 24 moves done with equal pattern counts, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if game has ended.
     *
     * Game ends after exactly 24 moves (board nearly full).
     *
     * @param player Pointer to player being checked
     * @return true if 24 moves completed, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Counts total three-in-a-row patterns for a symbol.
     *
     * Scans entire board in all 4 directions:
     * - Horizontal (→)
     * - Vertical (↓)
     * - Diagonal down-right (↘)
     * - Diagonal down-left (↙)
     *
     * For each starting position, checks if there are 3 consecutive
     * matching symbols. Overlapping patterns are counted separately.
     *
     * Example: "XXXX" contains 2 patterns: X[XXX] and [XXX]X
     *
     * @param symbol The symbol to count ('X' or 'O')
     * @return Total number of three-in-a-row patterns found
     */
    int count_three_in_a_row(char symbol);
};

/**
 * @class TicTacToe5x5_UI
 * @brief User interface for 5×5 Tic-Tac-Toe.
 *
 * Provides player setup and move input functionality with
 * intelligent AI that tries to maximize its three-in-a-row count.
 *
 * @see UI
 */
class TicTacToe5x5_UI : public UI<char> {
public:
    /**
     * @brief Constructs UI with welcome message.
     *
     * Displays "Welcome to 5x5 Tic-Tac-Toe Game!".
     */
    TicTacToe5x5_UI();

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
     * @brief Gets a move from player.
     *
     * For human players:
     * - Prompts for row and column (0-4)
     *
     * For computer players:
     * - Uses greedy strategy to maximize three-in-a-row count
     * - Tests each empty position to see which creates most patterns
     * - Selects position with highest score
     * - Falls back to random if no good move found
     *
     * AI strategy:
     * 1. Try each empty cell
     * 2. Count how many three-in-a-rows result
     * 3. Pick cell with best count
     *
     * @param player Pointer to player making move
     * @return Pointer to Move object with position and symbol
     */
    Move<char>* get_move(Player<char>* player) override;
};