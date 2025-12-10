/**
 * @file Diamond_Tic_Tac_Toe.h
 * @brief Defines classes for Diamond-shaped Tic-Tac-Toe game variant.
 *
 * This file contains the board, AI player, and UI classes for a unique
 * diamond-shaped Tic-Tac-Toe game played on a 7x7 grid where only
 * diamond-shaped cells are playable.
 *
 * @author Board Game Team
 * @date 2024
 */

#ifndef DIAMOND_TIC_TAC_TOE_H
#define DIAMOND_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;

/**
 * @class Diamond_Tic_Tac_Toe_Board
 * @brief Represents a diamond-shaped Tic-Tac-Toe board.
 *
 * This board is played on a 7x7 grid where only cells forming a diamond
 * shape are valid play positions. Players aim to get 4 marks in a row
 * (horizontal, vertical, or diagonal) to win. The board has 25 total
 * playable cells arranged in a diamond pattern.
 *
 * Board layout:
 * @code
 *       [0]
 *     [0][1][2]
 *   [0][1][2][3][4]
 * [0][1][2][3][4][5][6]
 *   [1][2][3][4][5]
 *     [2][3][4]
 *       [3]
 * @endcode
 *
 * @see Board
 */
class Diamond_Tic_Tac_Toe_Board : public Board<char> {
public:
    /**
     * @brief Constructs a 7x7 diamond-shaped board.
     *
     * Initializes a 7x7 grid where cells outside the diamond shape
     * are marked with '#' and playable cells are empty (' ').
     */
    Diamond_Tic_Tac_Toe_Board();

    /**
     * @brief Updates the board with a player's move.
     *
     * Validates that the move is within bounds, inside the diamond shape,
     * and the target cell is empty before applying the move.
     *
     * @param move Pointer to Move object containing position (x,y) and symbol
     * @return true if move is valid and applied successfully, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player has won by getting 4 in a row.
     *
     * Searches the entire board for any sequence of 4 matching symbols
     * in horizontal, vertical, or diagonal directions.
     *
     * @param player Pointer to player being checked
     * @return true if player has 4 marks in a row, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player has lost.
     *
     * @param player Pointer to player being checked
     * @return Always returns false (not used in this game variant)
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks if the game is a draw.
     *
     * The game is drawn when all 25 playable cells are filled
     * and no player has won.
     *
     * @param player Pointer to player being checked
     * @return true if all cells filled with no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game has ended.
     *
     * @param player Pointer to player being checked
     * @return true if game is won or drawn, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Checks if a cell is inside the diamond shape.
     *
     * Determines if the given coordinates fall within the valid
     * diamond-shaped play area.
     *
     * @param r Row index (0-6)
     * @param c Column index (0-6)
     * @return true if position is inside diamond, false otherwise
     */
    bool inside_diamond(int r, int c);

private:
    /**
     * @brief Checks for a line of matching symbols in a specific direction.
     *
     * @param sym Symbol to check for
     * @param r Starting row
     * @param c Starting column
     * @param dr Row direction (-1, 0, or 1)
     * @param dc Column direction (-1, 0, or 1)
     * @param needed Number of consecutive symbols needed
     * @return true if line of required length found, false otherwise
     */
    bool check_line(char sym, int r, int c, int dr, int dc, int needed);
};

/**
 * @class Diamond_AI_Player
 * @brief AI player implementation for Diamond Tic-Tac-Toe.
 *
 * Simple AI that selects the first available cell within the diamond
 * shape, prioritizing cells closer to the center.
 *
 * @see Player
 */
class Diamond_AI_Player : public Player<char> {
public:
    /**
     * @brief Constructs an AI player.
     *
     * @param n Player name
     * @param s Player symbol ('X' or 'O')
     */
    Diamond_AI_Player(string n, char s) : Player<char>(n, s, PlayerType::AI) {}

    /**
     * @brief Generates an AI move.
     *
     * Searches for the first empty cell within the diamond shape,
     * starting from positions closer to the center (row 3, col 3).
     *
     * @return Pointer to Move object, or nullptr if no valid moves
     */
    Move<char>* get_ai_move();
};

/**
 * @class Diamond_Tic_Tac_Toe_UI
 * @brief User interface for Diamond Tic-Tac-Toe game.
 *
 * Provides input/output functionality including board display with
 * proper diamond shape formatting and player move input.
 *
 * @see UI
 */
class Diamond_Tic_Tac_Toe_UI : public UI<char> {
public:
    /**
     * @brief Constructs the UI with game title.
     */
    Diamond_Tic_Tac_Toe_UI() : UI<char>("\n--- Diamond Tic Tac Toe ---", 2) {}

    /**
     * @brief Gets a move from a player.
     *
     * For human players, prompts for row and column input.
     * For AI players, calls the AI's move generation method.
     *
     * @param player Pointer to player making the move
     * @return Pointer to Move object representing the player's move
     */
    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI)
            return dynamic_cast<Diamond_AI_Player*>(player)->get_ai_move();

        int r, c;
        cout << player->get_name() << " (" << player->get_symbol()
            << ") enter row and column: ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }

    /**
     * @brief Creates a player of specified type.
     *
     * @param name Player name
     * @param symbol Player symbol
     * @param type Player type (HUMAN or AI)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::AI || type == PlayerType::COMPUTER)
            return new Diamond_AI_Player(name, symbol);

        return new Player<char>(name, symbol, PlayerType::HUMAN);
    }

    /**
     * @brief Displays the diamond-shaped board.
     *
     * Renders the board in a visually appealing diamond formation
     * with proper spacing and cell borders.
     *
     * @param mat The board matrix to display
     */
    void display_board_matrix(const vector<vector<char>>& mat) const;
};

#endif // DIAMOND_TIC_TAC_TOE_H