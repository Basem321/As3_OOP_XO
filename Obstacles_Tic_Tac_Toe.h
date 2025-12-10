/**
 * @file Obstacles_Tic_Tac_Toe.h
 * @brief Defines classes for Obstacles Tic-Tac-Toe game variant.
 *
 * This file implements a challenging Tic-Tac-Toe variant on a 6×6 board
 * where random obstacles are added after every 2 moves, and players must
 * connect 4 pieces in a row to win. The dynamic obstacles create an
 * unpredictable and strategic gameplay experience.
 *
 * @author Board Game Team
 * @date 2024
 */

#ifndef OBSTACLES_TIC_TAC_TOE_H
#define OBSTACLES_TIC_TAC_TOE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

#include "BoardGame_Classes.h"

using namespace std;

/**
 * @class Obstacles_Tic_Tac_Toe_Board
 * @brief Represents a 6×6 board with dynamic obstacle placement.
 *
 * Players compete on a 6×6 grid where:
 * - Goal is to connect 4 pieces in a row (horizontal, vertical, or diagonal)
 * - After every 2 moves (1 from each player), 1 random obstacle is added
 * - Obstacles ('#') block cells permanently
 * - Game is drawn if board fills with no winner
 *
 * Obstacle mechanics:
 * - Placed randomly in empty cells
 * - Cannot be removed or played on
 * - Added automatically after move pairs
 * - Adds strategic unpredictability
 *
 * Win condition: 4 in a row in any direction
 * Draw condition: Board full without any 4-in-a-row
 *
 * @see Board
 */
class Obstacles_Tic_Tac_Toe_Board : public Board<char> {
public:
    static const int ROWS = 6; ///< Board height (6 rows)
    static const int COLS = 6; ///< Board width (6 columns)

    /**
     * @brief Constructs a 6×6 board.
     *
     * Initializes all cells as empty ('.') and seeds random
     * number generator for obstacle placement.
     */
    Obstacles_Tic_Tac_Toe_Board();

    /**
     * @brief Virtual destructor.
     */
    virtual ~Obstacles_Tic_Tac_Toe_Board() override = default;

    /**
     * @brief Updates board with a player's move.
     *
     * Process:
     * 1. Validates position is in bounds and empty
     * 2. Places player's symbol
     * 3. Increments move counter
     * 4. If 2 moves completed (one per player), adds random obstacle
     *
     * @param move Pointer to Move object with position and symbol
     * @return true if move valid and placed, false if position occupied/invalid
     */
    virtual bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has won with 4 in a row.
     *
     * Scans entire board checking if any cell starts a line of
     * 4 matching symbols in any direction.
     *
     * @param player Pointer to player being checked
     * @return true if player has 4 consecutive pieces, false otherwise
     */
    virtual bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player has lost (opponent won).
     *
     * Checks if the opposing player has achieved 4 in a row.
     *
     * @param player Pointer to player being checked
     * @return true if opponent has 4 in a row, false otherwise
     */
    virtual bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if game is a draw.
     *
     * Game is drawn when:
     * - Board is completely filled, AND
     * - No player has achieved 4 in a row
     *
     * @param player Pointer to player being checked
     * @return true if board full with no winner, false otherwise
     */
    virtual bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if game has ended.
     *
     * @param player Pointer to player being checked
     * @return true if game won, lost, or drawn, false if game continues
     */
    virtual bool game_is_over(Player<char>* player) override;

    /**
     * @brief Adds random obstacles to empty cells.
     *
     * Randomly selects n empty cells and places obstacle markers ('#').
     * Uses modern C++ random shuffling for fair distribution.
     *
     * @param n Number of obstacles to add (default: 2)
     */
    void add_random_obstacles(int n = 2);

    /**
     * @brief Resets board to empty state.
     *
     * Clears all cells and resets move counter to 0.
     * Used for starting new games.
     */
    void clear_board();

    /**
     * @brief Gets list of all empty cell positions.
     *
     * Scans board and returns coordinates of all cells that
     * contain '.' (empty) rather than player symbols or obstacles.
     *
     * @return Vector of (row, col) pairs for empty cells
     */
    vector<pair<int, int>> get_empty_cells() const;

private:
    /**
     * @brief Checks for 4-in-a-row starting from specific position.
     *
     * Searches in all 4 directions (horizontal, vertical, both diagonals)
     * counting consecutive matching symbols in both forward and backward
     * directions from the starting cell.
     *
     * @param r Starting row
     * @param c Starting column
     * @param sym Symbol to check for
     * @return true if 4+ consecutive symbols found, false otherwise
     */
    bool four_in_a_row_from(int r, int c, char sym) const;

    /**
     * @brief Checks if board is completely filled.
     *
     * @return true if no empty cells remain, false otherwise
     */
    bool board_full() const;

    /**
     * @brief Tracks moves in current round (resets every 2 moves).
     *
     * Used to determine when to add obstacles. When reaches 2,
     * an obstacle is added and counter resets to 0.
     */
    int moves_this_round = 0;
};

/**
 * @class Obstacles_Tic_Tac_Toe_UI
 * @brief User interface for Obstacles Tic-Tac-Toe.
 *
 * Provides move input functionality and player creation for
 * the obstacles variant.
 *
 * @see UI
 */
class Obstacles_Tic_Tac_Toe_UI : public UI<char> {
public:
    /**
     * @brief Constructs UI with game title.
     */
    Obstacles_Tic_Tac_Toe_UI() : UI<char>("Obstacles Tic-Tac-Toe UI", 2) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~Obstacles_Tic_Tac_Toe_UI() override = default;

    /**
     * @brief Gets a move from player.
     *
     * For human players:
     * - Prompts for x and y coordinates (0 to 5)
     *
     * For computer players:
     * - Randomly selects position in 6×6 grid
     *
     * @param player Pointer to player making move
     * @return Pointer to Move object with position and symbol
     */
    virtual Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Creates a player of specified type.
     *
     * @param name Player name
     * @param symbol Player symbol ('X' or 'O')
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to new Player object
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif // OBSTACLES_TIC_TAC_TOE_H