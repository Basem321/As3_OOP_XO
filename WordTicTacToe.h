/**
 * @file WordTicTacToe.h
 * @brief Defines classes for Word Tic-Tac-Toe game variant.
 *
 * This file implements a word-based Tic-Tac-Toe variant where players
 * place letters (instead of X and O) on a 3×3 grid. The first player
 * to form a valid 3-letter dictionary word in any direction wins.
 *
 * @author Board Game Team
 * @date 2024
 */

#pragma once

#include "BoardGame_Classes.h"
#include <fstream>
#include <string>
#include <set>

using namespace std;

/**
 * @class WordTicTacToe_Board
 * @brief Represents a Word Tic-Tac-Toe board with dictionary validation.
 *
 * A 3×3 grid where:
 * - Players place individual letters (A-Z)
 * - Win by forming a valid 3-letter word
 * - Words checked in all directions (rows, columns, diagonals)
 * - Dictionary loaded from external file "dic.txt"
 *
 * Game mechanics:
 * - Any letter can be placed in any empty cell
 * - No restrictions on letter choice per player
 * - First valid word wins immediately
 * - Draw if board fills without forming valid words
 *
 * Word validation:
 * - Must be exactly 3 letters
 * - Must appear in loaded dictionary
 * - Case-insensitive (converted to uppercase)
 * - Checked after each move
 *
 * Dictionary format:
 * - Plain text file with one word per line
 * - Words converted to uppercase when loaded
 * - Stored in set for O(log n) lookup
 *
 * @see Board
 */
class WordTicTacToe_Board : public Board<char> {
private:
    set<string> dic;        ///< Dictionary of valid 3-letter words (uppercase)
    char blank_symbol = 0;  ///< Value representing empty cells

    /**
     * @brief Loads dictionary from text file.
     *
     * Reads words from file, converts to uppercase, and stores
     * in set for efficient lookup. Displays error if file not found.
     *
     * Expected file format:
     * @code
     * cat
     * dog
     * run
     * ...
     * @endcode
     *
     * @param filename Path to dictionary file (default: "dic.txt")
     */
    void load_dic(const string& filename);

public:
    /**
     * @brief Constructs a 3×3 word board and loads dictionary.
     *
     * Initializes empty board and loads words from "dic.txt".
     * Displays dictionary size or error message.
     */
    WordTicTacToe_Board();

    /**
     * @brief Updates board with a letter placement.
     *
     * Places letter (converted to uppercase) at specified position
     * if cell is empty.
     *
     * @param move Pointer to Move with position and letter
     * @return true if letter placed successfully, false if position occupied
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if a valid word has been formed.
     *
     * After at least 3 moves, checks all 8 possible lines:
     * - 3 rows (horizontal)
     * - 3 columns (vertical)
     * - 2 diagonals
     *
     * For each complete line (no empty cells), forms a 3-letter
     * string and checks if it exists in the dictionary.
     *
     * Word formation example:
     * @code
     * Row 0: [C][A][T] → "CAT" → Check if in dictionary
     * @endcode
     *
     * @param player Pointer to player being checked
     * @return true if any line forms valid dictionary word, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player has lost.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (not used in this variant)
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks if game is a draw.
     *
     * Draw occurs when all 9 cells are filled and no valid
     * words have been formed.
     *
     * @param player Pointer to player being checked
     * @return true if board full with no valid words, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if game has ended.
     *
     * Game ends when a valid word is formed OR board is full.
     *
     * @param player Pointer to player being checked
     * @return true if word found or board full, false otherwise
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class WordTicTacToe_UI
 * @brief User interface for Word Tic-Tac-Toe.
 *
 * Provides player setup, move input (letter + position), and
 * intelligent AI that attempts to form winning words.
 *
 * @see UI
 */
class WordTicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructs UI with welcome message.
     *
     * Displays "Welcome to Word Tic-Tac-Toe Game!".
     */
    WordTicTacToe_UI();

    /**
     * @brief Creates a player of specified type.
     *
     * Note: symbol parameter is used for player identification but
     * players actually place letters, not X/O symbols.
     *
     * @param name Player name
     * @param symbol Player identifier (used for turn tracking)
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to new Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a letter and position from player.
     *
     * For human players:
     * - Prompts for letter (A-Z)
     * - Validates input is alphabetic
     * - Prompts for position (row, col 0-2)
     *
     * For computer players:
     * - Uses intelligent strategy to find winning moves:
     *   1. Try all empty positions
     *   2. For each position, try all 26 letters
     *   3. Check if placement creates winning word
     *   4. If winning move found, use it
     *   5. Otherwise, random letter and position
     *
     * AI strategy:
     * @code
     * for each empty cell:
     *     for each letter A-Z:
     *         simulate placing letter
     *         if forms valid word:
     *             return this move
     * return random move
     * @endcode
     *
     * @param player Pointer to player making move
     * @return Pointer to Move with position and letter
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Sets up both players with explanation.
     *
     * Displays message explaining that players place letters
     * to form words, then calls base setup_players().
     *
     * @return Array of two Player pointers
     */
    Player<char>** setup_players() override;
};