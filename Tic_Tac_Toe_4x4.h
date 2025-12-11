/**
 * @file Tic_Tac_Toe_4x4.h
 * @brief Defines the Tic_Tac_Toe_4x4 (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `Tic_Tac_Toe_4x4_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `Tic_Tac_Toe_4x4_UI`: A user interface class tailored to Tic_Tac_Toe_4x4 game setup and player interaction.
 */

#ifndef Tic_Tac_Toe_4x4_H
#define Tic_Tac_Toe_4x4_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Tic_Tac_Toe_4x4_Board
 * @brief Represents the Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Tic-Tac-Toe (Tic_Tac_Toe_4x4) game, including
 * move updates, win/draw detection, and display functions.
 *
 * @see Board
 */
class Tic_Tac_Toe_4x4_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
    /**
     * @brief Default constructor that initializes a 3x3 Tic_Tac_Toe_4x4 board.
     */
    Tic_Tac_Toe_4x4_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in Tic_Tac_Toe_4x4 logic).
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has won, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class Tic_Tac_Toe_4x4_UI
 * @brief User Interface class for the Tic_Tac_Toe_4x4 (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * Tic_Tac_Toe_4x4?specific functionality for player setup and move input.
 *
 * @see UI
 */
class Tic_Tac_Toe_4x4_UI : public UI<char> {
public:
    /**
     * @brief Constructs an Tic_Tac_Toe_4x4_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "FCAI Tic_Tac_Toe_4x4".
     */
    Tic_Tac_Toe_4x4_UI();

    /**
     * @brief Destructor for Tic_Tac_Toe_4x4_UI.
     */
    ~Tic_Tac_Toe_4x4_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object representing the player's action.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

#endif // Tic_Tac_Toe_4x4_H
