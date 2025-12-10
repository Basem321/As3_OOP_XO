/**
 * @file SUS_Classes.h
 * @brief Defines classes for the SUS word-formation game.
 *
 * This file implements a unique 3×3 grid game where players place
 * 'S' and 'U' letters trying to form the word "SUS" in any direction.
 * Players score points for each "SUS" they complete, and the player
 * with the most points when the board fills wins.
 *
 * @author Board Game Team
 * @date 2024
 */

#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"

 /**
  * @class SUS_Board
  * @brief Represents the SUS game board with scoring system.
  *
  * A 3×3 grid where:
  * - Player 1 places 'S' letters
  * - Player 2 places 'U' letters
  * - Points are scored by completing "SUS" patterns
  * - Winner has most points when board is full
  *
  * Scoring rules:
  * - When 'S' is placed: Check for S-U-S patterns in all 8 directions
  * - When 'U' is placed: Check if it's sandwiched between two 'S'
  * - Each "SUS" found = 1 point for the player who completed it
  *
  * Patterns recognized:
  * - Horizontal: S-U-S (left-right)
  * - Vertical: S-U-S (up-down)
  * - Diagonal: S-U-S (both diagonals)
  *
  * Game end: Board fills (9 moves total)
  * Winner: Player with higher score
  * Draw: Equal scores
  *
  * @see Board
  */
class SUS_Board : public Board<char> {
private:
    int s_score; ///< Score for player placing 'S' letters
    int u_score; ///< Score for player placing 'U' letters

public:
    /**
     * @brief Constructs a 3×3 SUS board.
     *
     * Initializes empty board and sets both scores to 0.
     */
    SUS_Board();

    /**
     * @brief Updates board and calculates points for the move.
     *
     * Process:
     * 1. Validates position is empty
     * 2. Places the letter ('S' or 'U')
     * 3. Checks all directions for completed "SUS" patterns
     * 4. Awards points to the player who completed pattern(s)
     *
     * Point calculation:
     * - For 'S' placement: Check if it completes S-U-S starting from this S
     * - For 'U' placement: Check if it's between two existing S letters
     *
     * @param move Pointer to Move with position and symbol ('S' or 'U')
     * @return true if move valid and applied, false if position occupied
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has won (has higher score).
     *
     * Only evaluated when game is over (board full).
     *
     * @param player Pointer to player being checked
     * @return true if game over and player has higher score, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player has lost (has lower score).
     *
     * Only evaluated when game is over (board full).
     *
     * @param player Pointer to player being checked
     * @return true if game over and player has lower score, false otherwise
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if game is a draw (equal scores).
     *
     * Only evaluated when game is over (board full).
     *
     * @param player Pointer to player being checked
     * @return true if game over with equal scores, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if game has ended.
     *
     * Game ends when all 9 cells are filled.
     *
     * @param player Pointer to player being checked
     * @return true if 9 moves completed, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Gets current score for 'S' player.
     *
     * @return Number of "SUS" patterns completed by 'S' player
     */
    int get_s_score() const { return s_score; }

    /**
     * @brief Gets current score for 'U' player.
     *
     * @return Number of "SUS" patterns completed by 'U' player
     */
    int get_u_score() const { return u_score; }
};

/**
 * @class SUS_UI
 * @brief User interface for the SUS game.
 *
 * Handles player setup ensuring Player 1 gets 'S' and Player 2 gets 'U',
 * displays current scores during gameplay, and manages move input.
 *
 * @see UI
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructs SUS UI with welcome message.
     */
    SUS_UI();

    /**
     * @brief Creates a player with specified symbol.
     *
     * @param name Player name
     * @param symbol Player symbol ('S' or 'U')
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to new Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from player with score display.
     *
     * Before prompting for move, displays current scores.
     *
     * For human players:
     * - Shows current S and U scores
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

    /**
     * @brief Sets up both players with correct symbols.
     *
     * Ensures:
     * - Player 1 ("Player 1") gets symbol 'S'
     * - Player 2 ("Player 2") gets symbol 'U'
     *
     * @return Array of two Player pointers [S_player, U_player]
     */
    Player<char>** setup_players() override;
};

#endif // SUS_CLASSES_H