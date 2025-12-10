/**
 * @file Misere_Tic_Tac_Toe.h
 * @brief Defines classes for Misère Tic-Tac-Toe game variant.
 *
 * This file implements the Misère variant of Tic-Tac-Toe where the
 * objective is reversed: the first player to get three in a row LOSES.
 * Players must avoid creating three-in-a-row while trying to force
 * their opponent into that position.
 *
 * @author Dr El-Ramly
 * @date 2024
 */

#ifndef Misere_Tic_Tac_Toe_H
#define Misere_Tic_Tac_Toe_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Misere_Tic_Tac_Toe_Board
 * @brief Represents a Misère Tic-Tac-Toe board with reversed win condition.
 *
 * A standard 3×3 Tic-Tac-Toe board where getting three in a row means
 * you LOSE rather than win. This creates a strategic game where players
 * must balance offense and defense differently than traditional Tic-Tac-Toe.
 *
 * Game rules:
 * - 3×3 grid
 * - Getting 3 in a row = you LOSE
 * - Filling the board without 3 in a row = you WIN
 * - No draws (if board fills, whoever didn't make 3-in-a-row wins)
 *
 * Win/Lose logic:
 * - is_lose(): Returns true if player made 3-in-a-row (they lose)
 * - is_win(): Returns true if board full and player didn't make 3-in-a-row
 *
 * @see Board
 */
class Misere_Tic_Tac_Toe_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character representing empty cells

public:
    /**
     * @brief Constructs a 3×3 Misère board.
     *
     * Initializes all cells with blank symbol.
     */
    Misere_Tic_Tac_Toe_Board();

    /**
     * @brief Updates board with a player's move.
     *
     * Validates position and places piece. Also supports move undo
     * when symbol is 0 (used for AI search/backtracking).
     *
     * @param move Pointer to Move object (symbol=0 for undo)
     * @return true if move valid and applied, false otherwise
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if player has WON (survived without 3-in-a-row).
     *
     * Player wins if:
     * - Board is completely filled (9 moves), AND
     * - Player did NOT create three-in-a-row
     *
     * @param player Pointer to player being checked
     * @return true if board full and player avoided 3-in-a-row, false otherwise
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if player has LOST (made three-in-a-row).
     *
     * Player loses immediately if they create three matching symbols in:
     * - Any row (horizontal)
     * - Any column (vertical)
     * - Either diagonal
     *
     * @param player Pointer to player being checked
     * @return true if player created 3-in-a-row (loses), false otherwise
     */
    bool is_lose(Player<char>* player);

    /**
     * @brief Checks if game is a draw.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (no draws in Misère variant)
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks if game has ended.
     *
     * Game ends when:
     * - A player loses (makes 3-in-a-row), OR
     * - A player wins (board full without making 3-in-a-row)
     *
     * @param player Pointer to player being checked
     * @return true if game over, false if game continues
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class Misere_Tic_Tac_Toe_UI
 * @brief User interface for Misère Tic-Tac-Toe.
 *
 * Provides player setup and move input functionality with
 * proper display of the reversed-objective rules.
 *
 * @see UI
 */
class Misere_Tic_Tac_Toe_UI : public UI<char> {
public:
    /**
     * @brief Constructs UI with game title.
     *
     * Displays "FCAI Misere Tic Tac Toe Game by Dr El-Ramly".
     */
    Misere_Tic_Tac_Toe_UI();

    /**
     * @brief Destructor.
     */
    ~Misere_Tic_Tac_Toe_UI() {};

    /**
     * @brief Creates a player of specified type.
     *
     * Displays creation message showing player type and symbol.
     *
     * @param name Player name
     * @param symbol Player symbol ('X' or 'O')
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to new Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Gets a move from a player.
     *
     * For human players:
     * - Prompts "enter x and y (0 to 2)"
     * - Reads row and column input
     *
     * For computer players:
     * - Randomly selects position within bounds
     *
     * @param player Pointer to player making move
     * @return Pointer to Move object with position and symbol
     */
    virtual Move<char>* get_move(Player<char>* player);
};

#endif // Misere_Tic_Tac_Toe_H