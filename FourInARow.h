/**
 * @file FourInARow.h
 * @brief Defines classes for Four-in-a-Row (Connect Four) game.
 *
 * This file contains the implementation of the classic Connect Four game
 * where players drop pieces into columns and try to connect four pieces
 * vertically, horizontally, or diagonally.
 *
 * @author Board Game Team
 * @date 2024
 */

#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"

using namespace std;

/**
 * @class FourInARow_Board
 * @brief Represents a Connect Four game board.
 *
 * The board is a 6-row by 7-column grid where pieces fall to the
 * lowest available position in the selected column. Players win by
 * connecting four pieces in a row horizontally, vertically, or diagonally.
 *
 * Board dimensions: 6 rows × 7 columns (42 total cells)
 *
 * Game rules:
 * - Players alternate dropping pieces into columns
 * - Pieces fall to the lowest available row in that column
 * - First to connect 4 pieces in any direction wins
 * - Game is a draw if board fills with no winner
 *
 * @see Board
 */
class FourInARow_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character representing empty cells

    /**
     * @brief Finds the lowest empty row in a column.
     *
     * Searches from bottom to top to find the first empty cell
     * where a piece can be placed.
     *
     * @param col Column index (0-6)
     * @return Row index of lowest empty cell, or -1 if column is full
     */
    int find_lowest_row(int col);

public:
    /**
     * @brief Constructs a 6×7 Four-in-a-Row board.
     *
     * Initializes all cells with the blank symbol ('.').
     */
    FourInARow_Board();

    /**
     * @brief Updates board with a player's move.
     *
     * Takes the column from the move's y-coordinate and drops
     * the piece to the lowest available row in that column.
     * Validates that the column exists and is not full.
     *
     * @param move Pointer to Move object (y value is column, x is ignored)
     * @return true if piece successfully placed, false if column full or invalid
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has won with 4 in a row.
     *
     * Searches all possible lines of 4 cells in all directions:
     * - Horizontal (→)
     * - Vertical (↓)
     * - Diagonal down-right (↘)
     * - Diagonal down-left (↙)
     *
     * @param player Pointer to player being checked
     * @return true if player has 4 consecutive pieces, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player has lost.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (not used in this game)
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks if game is a draw.
     *
     * Game is drawn when all 42 cells are filled and no player has won.
     *
     * @param player Pointer to player being checked
     * @return true if board full with no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if game has ended.
     *
     * @param player Pointer to player being checked
     * @return true if game is won or drawn, false otherwise
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class FourInARow_UI
 * @brief User interface for Four-in-a-Row game.
 *
 * Provides game setup, player creation, move input, and displays
 * game rules and instructions to users.
 *
 * @see UI
 */
class FourInARow_UI : public UI<char> {
public:
    /**
     * @brief Constructs the UI and displays game rules.
     *
     * Shows welcome message and explains:
     * - Board dimensions (6×7)
     * - How to choose columns (0-6)
     * - Win condition (4 in a row)
     * - Draw condition
     */
    FourInARow_UI();

    /**
     * @brief Destructor.
     */
    ~FourInARow_UI() {}

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
     * - Prompts for column number (0-6)
     * - Validates input is a valid integer in range
     *
     * For computer players:
     * - Randomly selects an available column
     * - Uses fallback search if random selection fails
     *
     * @param player Pointer to player making the move
     * @return Pointer to Move object with column in y-coordinate
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif // FOUR_IN_A_ROW_H