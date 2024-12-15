#include <iostream>
#include "BoardGame_Classes.h"
#include "PyramdicX_O.h"
#include "Word_TTO.h"
#include "Token_X_O.h"
#include "5x5X_O.h"
#include "Misere_X_O_.h"

using namespace std;

// Generic function to set up players
template <typename HumanPlayerCreator, typename RandomPlayerCreator>
void setupPlayers(Player<char>* players[], HumanPlayerCreator createHumanPlayer, RandomPlayerCreator createRandomPlayer) {
    string playerName;
    int choice;

    for (int i = 0; i < 2; ++i) {
        cout << "Enter Player " << (i == 0 ? "1" : "2") << " name: ";
        cin >> playerName;

        cout << "Choose Player " << (i == 0 ? "1" : "2") << " type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch (choice) {
            case 1:
                players[i] = createHumanPlayer(playerName, i == 0 ? 'X' : 'O');
                break;
            case 2:
                players[i] = createRandomPlayer(i == 0 ? 'X' : 'O');
                break;
            default:
                cout << "Invalid choice for Player " << (i + 1) << ". Exiting the game.\n";
                exit(1);
        }
    }
}

int main() {
    int choice;
    cout << "Choose which game to play:" << endl;
    cout << "1 - Pyramidic Tic-Tac-Toe\n";
    cout << "2 - Word Tic-Tac-Toe\n";
    cout << "3 - Token Tick-Tack-Toe\n";
    cout << "4 - 5x5 Tic-Tac-Toe\n";
    cout << "5 - Misere Toe-Tack-Tick\n";
    cin >> choice;

    Player<char>* players[2] = {nullptr, nullptr};

    switch (choice) {
        case 1: { // Pyramidic Tic-Tac-Toe
            auto* board = new Pyramid_Board<char>();
            setupPlayers(
                players,
                [](const string& name, char symbol) { return new Pyramid_Player<char>(name, symbol); },
                [](char symbol) { return new Random_Pyramid_Player<char>(symbol); }
            );
            GameManager<char> game(board, players);
            game.run();
            delete board;
            break;
        }
        case 2: { // Word Tic-Tac-Toe
            auto* board = new Word_Board<char>();
            setupPlayers(
                players,
                [](const string& name, char) { return new Word_Player<char>(name); },
                [](char) { return new Random_Word_Player<char>(); }
            );
            GameManager<char> game(board, players);
            game.run();
            delete board;
            break;
        }
        case 3: { // Token Tic-Tac-Toe
            auto* board = new Token_X_O_Board<char>();
            setupPlayers(
                players,
                [](const string& name, char symbol) { return new Token_X_O_Player<char>(name, symbol); },
                [](char symbol) { return new Token_X_O_Random_Player<char>(symbol); }
            );
            GameManager<char> game(board, players);
            game.run();
            delete board;
            break;
        }
        case 4: { // 5x5 Tic-Tac-Toe
            auto* board = new _5_X_O_Board<char>();
            setupPlayers(
                players,
                [](const string& name, char symbol) { return new _5x5_X_O_player<char>(name, symbol); },
                [](char symbol) { return new _5x5_X_O_Random_Player<char>(symbol); }
            );
            GameManager<char> game(board, players);
            game.run();
            delete board;
            break;
        }
        case 5: { // Misere Tic-Tac-Toe
            auto* board = new Misere_X_O_Board<char>();
            setupPlayers(
                players,
                [](const string& name, char symbol) { return new Misere_X_O_Player<char>(name, symbol); },
                [](char symbol) { return new Misere_X_O_Random_Player<char>(symbol); }
            );
            GameManager<char> game(board, players);
            game.run();
            delete board;
            break;
        }
        default:
            cout << "Invalid game choice. Exiting.\n";
            return 1;
    }

    delete players[0];
    delete players[1];
    return 0;
}
