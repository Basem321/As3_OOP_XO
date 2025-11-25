#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Numerical_tic_tac_9.h"
#include "SUS_Classes.h"
#include "TicTacToe5x5.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;

    cout << "=============================================" << endl;
    cout << "  Welcome to FCAI Al3ab gamda moot (Team  )" << endl;
    cout << "=============================================" << endl;
    cout << "Menu:" << endl;
    cout << "  1. Play X-O Game (Demo)" << endl;
    cout << "  2. Play SUS Game" << endl;
    cout << "  3. Play 5x5 Tic-Tac-Toe" << endl;
    cout << "  9. Play Numerical Tic-Tac-Toe" << endl;
    cout << "  0. Exit" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
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
    else if (choice == 2) {
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
    else if (choice != 0) {
        cout << "Invalid choice. Exiting." << endl;
    }

    cout << "\nThank you for playing!" << endl;
    return 0;
}