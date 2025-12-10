/**
 * @file Numerical_tic_tac_9.h
 * @brief Defines classes for Numerical Tic-Tac-Toe game variant.
 *
 * This file implements a strategic Tic-Tac-Toe variant where players
 * use numbers instead of X and O. Player 1 uses odd numbers (1,3,5,7,9)
 * and Player 2 uses even numbers (2,4,6,8). Players win by creating
 * a line that sums to exactly 15.
 *
 * @author Board Game Team
 * @date 2024
 */

#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <set>
#include <algorithm>

 /**
  * @class Numerical_Board
  * @brief Represents a Numerical Tic-Tac-Toe board.
  *
  * A 3×3 board where players place numbers instead of symbols. The game
  * uses a magic square principle where any line (row, column, or diagonal)
  * that sums to 15 wins the game.
  *
  * Number allocation:
  * - Player 1 (symbol=1): Uses odd numbers {1, 3, 5, 7, 9}
  * - Player 2 (symbol=2): Uses even numbers {2, 4, 6, 8}
  *
  * Win condition:
  * - Any complete row, column, or diagonal that sums to exactly 15
  *
  * Draw condition:
  * - All 9 cells filled without any sum of 15
  *
  * Strategic depth:
  * - Each number can only be used once
  * - Players must balance using small vs large numbers
  * - Multiple potential winning lines to defend/attack
  *
  * @see Board
  */
class Numerical_Board : public Board<int> {
private:
    set<int> used_numbers;  ///< Tracks all numbers already placed on board
    set<int> Player_Odd;    ///< Available odd numbers for Player 1 {1,3,5,7,9}
    set<int> Player_Even;   ///< Available even numbers for Player 2 {2,4,6,8}
    int blank_value = 0;    ///< Value representing empty cells

public:
    /**
     * @brief Constructs a 3×3 numerical board.
     *
     * Initializes:
     * - Empty 3×3 grid (all cells = 0)
     * - Player_Odd set with {1, 3, 5, 7, 9}
     * - Player_Even set with {2, 4, 6, 8}
     * - Empty used_numbers set
     */
    Numerical_Board();

    /**
     * @brief Updates board with a player's number placement.
     *
     * Validates:
     * - Position is in bounds and empty
     * - Number hasn't been used before
     * - Number belongs to current player's set
     *
     * Special case: symbol=0 allows undo of a move
     *
     * @param move Pointer to Move<int> with position and number
     * @return true if number valid and placed, false otherwise
     */
    bool update_board(Move<int>* move) override;

    /**
     * @brief Checks if any line sums to 15.
     *
     * Examines all 8 possible winning lines:
     * - 3 rows
     * - 3 columns
     * - 2 diagonals
     *
     * A line wins if:
     * - All 3 cells are filled (non-zero), AND
     * - The sum equals exactly 15
     *
     * @param player Pointer to player being checked
     * @return true if any complete line sums to 15, false otherwise
     */
    bool is_win(Player<int>* player) override;

    /**
     * @brief Checks if player has lost.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (not used in this variant)
     */
    bool is_lose(Player<int>* player) override { return false; }

    /**
     * @brief Checks if game is a draw.
     *
     * Game is drawn when all 9 cells are filled and no line
     * sums to 15.
     *
     * @param player Pointer to player being checked
     * @return true if board full with no sum of 15, false otherwise
     */
    bool is_draw(Player<int>* player) override;

    /**
     * @brief Checks if game has ended.
     *
     * @param player Pointer to player being checked
     * @return true if game won or drawn, false if game continues
     */
    bool game_is_over(Player<int>* player) override;

    /**
     * @brief Validates if a number can be used by a player.
     *
     * Checks:
     * - Number hasn't been used before
     * - Number is in player's available set (odd or even)
     *
     * @param number The number to validate
     * @param player Pointer to player attempting to use the number
     * @return true if number valid for player, false otherwise
     */
    bool is_valid_number(int number, Player<int>* player);

    /**
     * @brief Gets all unused numbers available to a player.
     *
     * Returns the player's number set (odd or even) minus
     * any numbers already placed on the board.
     *
     * @param player Pointer to player requesting available numbers
     * @return Set of integers the player can still use
     */
    set<int> get_available_numbers(Player<int>* player);
};

/**
 * @class Numerical_UI
 * @brief User interface for Numerical Tic-Tac-Toe.
 *
 * Provides game setup, displays rules about odd/even number usage
 * and the sum-to-15 win condition, and handles move input.
 *
 * @see UI
 */
class Numerical_UI : public UI<int> {
public:
    /**
     * @brief Constructs UI and displays game rules.
     *
     * Shows:
     * - Player 1 uses odd numbers: 1, 3, 5, 7, 9
     * - Player 2 uses even numbers: 2, 4, 6, 8
     * - Each number can only be used once
     * - Win by getting sum of 15 in any line
     */
    Numerical_UI();

    /**
     * @brief Destructor.
     */
    ~Numerical_UI() {}

    /**
     * @brief Creates a player with numeric symbol.
     *
     * Symbol meanings:
     * - 1 = Player using odd numbers
     * - 2 = Player using even numbers
     *
     * @param name Player name
     * @param symbol Player identifier (1 for odd, 2 for even)
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to new Player<int> object
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;

    /**
     * @brief Gets a number placement move from player.
     *
     * For human players:
     * - Displays available numbers
     * - Prompts for number selection
     * - Validates number is available
     * - Prompts for position (row, col)
     *
     * For computer players:
     * - Randomly selects from available numbers
     * - Randomly selects empty cell
     *
     * @param player Pointer to player making move
     * @return Pointer to Move<int> with position and number
     */
    Move<int>* get_move(Player<int>* player) override;

    /**
     * @brief Sets up both players with correct symbols.
     *
     * Ensures Player 1 gets symbol 1 (odd numbers) and
     * Player 2 gets symbol 2 (even numbers).
     *
     * @return Array of two Player<int> pointers
     */
    Player<int>** setup_players() override;
};

#endif // NUMERICAL_TICTACTOE_H