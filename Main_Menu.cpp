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

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;

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
    cout << "  9. Play Numerical Tic-Tac-Toe" << endl;
    cout << " 10. Play Obstacles Tic-Tac-Toe" << endl;
    cout << " 11. Play Infinity Tic-Tac-Toe" << endl;
    cout << " 12. Play Ultimate Tic-Tac-Toe" << endl;
    cout << "  0. Exit" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

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
    else if (choice != 0) {
        cout << "Invalid choice. Exiting." << endl;
    }

    cout << "\nThank you for playing!" << endl;
    return 0;
}