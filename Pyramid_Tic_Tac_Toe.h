/**
 * @file Pyramid_Tic_Tac_Toe_Classes.h
 * @brief Defines the Pyramid_Tic_Tac_Toe (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `Pyramid_Tic_Tac_Toe_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `Pyramid_Tic_Tac_Toe_UI`: A user interface class tailored to Pyramid_Tic_Tac_Toe game setup and player interaction.
 */

#ifndef PYRAMID_TIC_TAC_TOE_H
#define PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Pyramid_Tic_Tac_Toe_Board
 * @brief Represents the Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Tic-Tac-Toe (Pyramid_Tic_Tac_Toe) game, including
 * move updates, win/draw detection, and display functions.
 *
 * @see Board
 */
class Pyramid_Tic_Tac_Toe_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
    /**
     * @brief Default constructor that initializes a 3x3 Pyramid_Tic_Tac_Toe board.
     */
    Pyramid_Tic_Tac_Toe_Board();

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
     * @return Always returns false (not used in Pyramid_Tic_Tac_Toe logic).
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
 * @class Pyramid_Tic_Tac_Toe_UI
 * @brief User Interface class for the Pyramid_Tic_Tac_Toe (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * Pyramid_Tic_Tac_Toe?specific functionality for player setup and move input.
 *
 * @see UI
 */
class Pyramid_Tic_Tac_Toe_UI : public UI<char> {
public:
    /**
     * @brief Constructs an Pyramid_Tic_Tac_Toe_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "FCAI Pyramid_Tic_Tac_Toe".
     */
    Pyramid_Tic_Tac_Toe_UI();

    /**
     * @brief Destructor for Pyramid_Tic_Tac_Toe_UI.
     */
    ~Pyramid_Tic_Tac_Toe_UI() {};

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

#endif // Pyramid_Tic_Tac_Toe_CLASSES_H
