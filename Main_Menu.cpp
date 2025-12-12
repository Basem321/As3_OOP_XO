/**
 * @file Main_Menu.cpp
 * @brief Main entry point for the Board Game Collection.
 *
 * This file provides a menu-driven interface for selecting and playing
 * various Tic-Tac-Toe variants and Connect Four. It handles game
 * initialization, player setup, game execution, and cleanup for all
 * supported game types.
 *
 * @author FCAI Board Game Team
 * @date 2024
 * @version 1.0
 */

 /**
  * @mainpage FCAI Board Game Collection
  *
  * @section intro_sec Introduction
  *
  * Welcome to the FCAI Board Game Collection! This project implements
  * a comprehensive framework for board games, with 12 different
  * Tic-Tac-Toe variants and the classic Connect Four game.
  *
  * @section features_sec Features
  *
  * The collection includes:
  * - **Template-based Game Framework**: Generic classes for boards, players, and moves
  * - **12 Game Variants**: From classic Tic-Tac-Toe to complex Ultimate variant
  * - **AI Support**: Computer opponents for all games
  * - **Extensible Design**: Easy to add new game variants
  * - **Clean Architecture**: Separation of game logic, UI, and data
  *
  * @section games_sec Available Games
  *
  * 1. **X-O Game (Demo)**: Classic 3×3 Tic-Tac-Toe
  * 2. **Four-in-a-Row**: Connect Four on 6×7 grid
  * 3. **SUS Game**: Form "SUS" patterns to score points
  * 4. **5×5 Tic-Tac-Toe**: Count three-in-a-rows on larger board
  * 5. **Word Tic-Tac-Toe**: Place letters to form dictionary words
  * 6. **Misère Tic-Tac-Toe**: Avoid getting three in a row
  * 7. **Diamond Tic-Tac-Toe**: Play on diamond-shaped 7×7 board
  * 8. **Numerical Tic-Tac-Toe**: Use numbers to sum to 15
  * 9. **Obstacles Tic-Tac-Toe**: Dynamic obstacles on 6×6 board
  * 10. **Infinity Tic-Tac-Toe**: Only 3 pieces per player at a time
  * 11. **Ultimate Tic-Tac-Toe**: Meta-game of 9 boards
  *
  * @section arch_sec Architecture
  *
  * The project uses a template-based inheritance hierarchy:
  *
  * @code
  * Board<T>                    Player<T>               UI<T>
  *    ↑                           ↑                      ↑
  *    |                           |                      |
  * Specific                   Specific               Specific
  * Game Boards                AI Players             Game UIs
  * @endcode
  *
  * Key components:
  * - **Board<T>**: Abstract base for game boards
  * - **Player<T>**: Represents human and computer players
  * - **Move<T>**: Encapsulates a single move
  * - **UI<T>**: Handles input/output for games
  * - **GameManager<T>**: Orchestrates game flow
  *
  * @section usage_sec Usage
  *
  * To add a new game variant:
  *
  * 1. Create a board class inheriting from Board<T>
  * 2. Implement required virtual methods (update_board, is_win, etc.)
  * 3. Create a UI class inheriting from UI<T>
  * 4. Optionally create custom AI player class
  * 5. Add to main menu
  *
  * Example:
  * @code
  * class MyBoard : public Board<char> {
  *     bool update_board(Move<char>* move) override { ... }
  *     bool is_win(Player<char>* player) override { ... }
  *     // ... other methods
  * };
  *
  * class MyUI : public UI<char> {
  *     Move<char>* get_move(Player<char>* player) override { ... }
  *     Player<char>* create_player(...) override { ... }
  * };
  * @endcode
  *
  * @section compile_sec Compilation
  *
  * Requires C++11 or later:
  * @code
  * g++ -std=c++11 Main_Menu.cpp [other files] -o game
  * ./game
  * @endcode
  *
  * @section deps_sec Dependencies
  *
  * - Standard Template Library (STL)
  * - For WordTicTacToe: dic.txt file with valid 3-letter words
  *
  * @section authors_sec Authors
  *
  * FCAI Board Game Team
  * - Dr. El-Ramly (Framework Design)
  * - Various contributors for game implementations
  *
  * @section license_sec License
  *
  * Educational use for FCAI courses.
  */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Misere_Tic_Tac_Toe.h"
#include "Numerical_tic_tac_9.h"
#include "SUS_Classes.h"
#include "TicTacToe5x5.h"
#include "Infinity_TicTacToe.h"
#include "FourInARow.h"
#include "WordTicTacToe.h"
#include "Diamond_Tic_Tac_Toe.h"
#include "UltimateTicTacToe.h"
#include "Obstacles_Tic_Tac_Toe.h"
#include "MemoryTTT_Classes.h"
#include "Tic_Tac_Toe_4x4.h"

using namespace std;

/**
 * @brief Main function providing game selection menu.
 *
 * Displays a menu of available games, handles user selection,
 * initializes the chosen game with appropriate board and UI classes,
 * runs the game to completion, and performs cleanup.
 *
 * Menu options (0-12):
 * - 0: Exit program
 * - 1: Four-in-a-Row (Connect Four)
 * - 2: SUS Game
 * - 3: 5×5 Tic-Tac-Toe
 * - 4: Word Tic-Tac-Toe
 * - 5: Misère Tic-Tac-Toe
 * - 6: Diamond Tic-Tac-Toe
 * - 9: Numerical Tic-Tac-Toe
 * - 10: Obstacles Tic-Tac-Toe
 * - 11: Infinity Tic-Tac-Toe
 * - 12: Ultimate Tic-Tac-Toe
 *
 * Game lifecycle for each selection:
 * 1. Create UI object
 * 2. Create Board object
 * 3. Setup players via UI
 * 4. Create GameManager
 * 5. Run game
 * 6. Delete all dynamically allocated objects
 *
 * Memory management:
 * - All dynamically allocated objects are properly deleted
 * - Player array and individual players cleaned up after each game
 * - Board and UI objects deleted before exit
 *
 * @return 0 on successful execution
 *
 * @note Seeds random number generator at startup for computer players
 * @note Invalid menu choices display error message and exit
 *
 * Example usage flow:
 * @code
 * // User runs program
 * $ ./game
 *
 * // Sees menu
 * Welcome to FCAI Board Games...
 * Menu:
 *   1. Play Four-in-a-Row
 *   ...
 * Enter your choice: 3
 *
 * // Game initializes
 * Starting 5x5 Tic-Tac-Toe...
 * Setup players...
 *
 * // Game runs
 * [Game plays out]
 *
 * // Cleanup and exit
 * Thank you for playing!
 * @endcode
 */
int main() {
    // Seed random number generator for computer players
    srand(static_cast<unsigned int>(time(0)));

    int choice;

    // Display main menu
    cout << "=============================================" << endl;
    cout << "  Welcome to FCAI Al3ab gamda moot (Team  )" << endl;
    cout << "=============================================" << endl;
    cout << "Menu:" << endl;
    cout << "  0. Play X-O Game (Demo)" << endl;
    cout << "  1. Play Four-in-a-Row (Connect Four)" << endl;
    cout << "  2. Play SUS Game" << endl;
    cout << "  3. Play 5x5 Tic-Tac-Toe" << endl;
    cout << "  4. Play Word Tic-Tac-Toe" << endl;
    cout << "  5. Play Misere Tic Tac Toe" << endl;
    cout << "  6. Play Diamond Tic Tac Toe" << endl;
    cout << "  7. Play 4x4 Tic-Tac-Toe" << endl;
    cout << "  8. Play Prmaid Tic-Tac-Toe" << endl;
    cout << "  9. Play Numerical Tic-Tac-Toe" << endl;
    cout << " 10. Play Obstacles Tic-Tac-Toe" << endl;
    cout << " 11. Play Infinity Tic-Tac-Toe" << endl;
    cout << " 12. Play Ultimate Tic-Tac-Toe" << endl;
    cout << " 13. Play Memory_Tic_Tac_Toe" << endl;
    cout << "  0. Exit" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    /**
     * @section game_handlers Game Handler Sections
     *
     * Each game handler follows the same pattern:
     * 1. Display starting message
     * 2. Create UI (handles input/output)
     * 3. Create Board (handles game logic)
     * 4. Setup players through UI
     * 5. Create GameManager to orchestrate
     * 6. Run game to completion
     * 7. Clean up all allocated memory
     */

    if (choice == 0) {
        cout << "\nLets play X-O Together..." << endl;

        UI<char>* game_ui = new XO_UI();
        Board<char>* xo_board = new X_O_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> x_o_game(xo_board, players, game_ui);

        x_o_game.run();

        delete xo_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 1) {
        cout << "\nLets play SUS Game..." << endl;

        UI<char>* game_ui = new SUS_UI();
        Board<char>* sus_board = new SUS_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> sus_game(sus_board, players, game_ui);

        sus_game.run();

        delete sus_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 2) {
        cout << "\nStarting Four-in-a-Row (Connect Four)..." << endl;

        UI<char>* game_ui = new FourInARow_UI();
        Board<char>* board = new FourInARow_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> game(board, players, game_ui);

        game.run();

        delete board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 3) {
        cout << "\nStarting 5x5 Tic-Tac-Toe..." << endl;

        UI<char>* game_ui = new TicTacToe5x5_UI();
        Board<char>* board = new TicTacToe5x5();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> game(board, players, game_ui);

        game.run();

        delete board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 4) {
        cout << "\nStarting Word Tic-Tac-Toe..." << endl;

        UI<char>* game_ui = new WordTicTacToe_UI();
        Board<char>* word_board = new WordTicTacToe_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> word_game(word_board, players, game_ui);

        word_game.run();

        delete word_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 5) {
        cout << "\nLets play Misere Tic Tac Toe Together..." << endl;

        UI<char>* game_ui = new Misere_Tic_Tac_Toe_UI();
        Board<char>* Misere_Tic_Tac_Toe_board = new Misere_Tic_Tac_Toe_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> Misere_Tic_Tac_Toe_game(Misere_Tic_Tac_Toe_board, players, game_ui);

        Misere_Tic_Tac_Toe_game.run();

        delete Misere_Tic_Tac_Toe_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 6) {
        cout << "\nLets play Diamond Tic Tac Toe Together..." << endl;

        UI<char>* game_ui = new Diamond_Tic_Tac_Toe_UI();
        Board<char>* Diamond_Tic_Tac_Toe_board = new Diamond_Tic_Tac_Toe_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> Diamond_Tic_Tac_Toe_game(Diamond_Tic_Tac_Toe_board, players, game_ui);

        Diamond_Tic_Tac_Toe_game.run();

        delete Diamond_Tic_Tac_Toe_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
	}
	else if (choice == 7) {
		cout << "\nStarting 4x4 Tic-Tac-Toe..." << endl;

		UI<char>* game_ui = new Tic_Tac_Toe_4x4_UI();
		Board<char>* board = new Tic_Tac_Toe_4x4_Board();
		Player<char>** players = game_ui->setup_players();
		GameManager<char> game(board, players, game_ui);

		game.run();

		delete board;
		delete players[0];
		delete players[1];
		delete[] players;
		delete game_ui;
		}
    else if (choice == 9) {
        cout << "\nLaunching Numerical Tic-Tac-Toe..." << endl;

        UI<int>* game_ui = new Numerical_UI();
        Board<int>* num_board = new Numerical_Board();
        Player<int>** players = game_ui->setup_players();
        GameManager<int> num_game(num_board, players, game_ui);

        num_game.run();

        delete num_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 10) {
        cout << "\nLets play Obstacles Tic Tac Toe Together..." << endl;

        UI<char>* game_ui = new Obstacles_Tic_Tac_Toe_UI();
        Board<char>* Obstacles_Tic_Tac_Toe_board = new Obstacles_Tic_Tac_Toe_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> Obstacles_Tic_Tac_Toe_game(Obstacles_Tic_Tac_Toe_board, players, game_ui);

        Obstacles_Tic_Tac_Toe_game.run();

        delete Obstacles_Tic_Tac_Toe_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 11) {
        cout << "\nLaunching Infinity Tic-Tac-Toe..." << endl;

        UI<char>* game_ui = new Infinity_UI();
        Board<char>* infinity_board = new Infinity_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> infinity_game(infinity_board, players, game_ui);

        infinity_game.run();

        delete infinity_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 12) {
        cout << "\nLaunching Ultimate Tic-Tac-Toe..." << endl;

        UI<char>* game_ui = new UltimateTicTacToe_UI();
        Board<char>* ultimate_board = new UltimateTicTacToe_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> ultimate_game(ultimate_board, players, game_ui);

        ultimate_game.run();

        delete ultimate_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice == 13) {
        cout << "\nLets play Memory Tic Tac Toe Together..." << endl;

        UI<char>* game_ui = new MemoryTTT_UI();
        Board<char>* memory_board = new MemoryTTT_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> memory_game(memory_board, players, game_ui);

        memory_game.run();

        delete memory_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
        }
    else if (choice != 0) {
        cout << "Invalid choice. Exiting." << endl;
    }

    cout << "\nThank you for playing!" << endl;
    return 0;
}