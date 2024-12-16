#include <iostream>
#include "BoardGame_Classes.h"
#include "PyramdicX_O.h"
#include "Word_TTO.h"
#include "Token_X_O.h"
#include "5x5X_O.h"
#include "Misere_X_O_.h"
#include "FourInRow.h"
#include "Ultimate_TicTacToe.h"
#include "3x3_Num_TicTacToe.h"

using namespace std;

// Generic function to set up players
template <typename HumanPlayerCreator, typename RandomPlayerCreator>
void setupPlayers(Player<char> *players[], HumanPlayerCreator createHumanPlayer, RandomPlayerCreator createRandomPlayer)
{
    string playerName;
    int choice;

    for (int i = 0; i < 2; ++i)
    {
        cout << "Enter Player " << (i == 0 ? "1" : "2") << " name: ";
        cin >> playerName;

        /*
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
        */

        while (true)
        {
            cout << "Choose Player " << (i == 0 ? "1" : "2") << " type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number (1 or 2).\n";
                continue;
            }

            cin >> choice;
            if (choice == 1)
            {
                players[i] = createHumanPlayer(playerName, i == 0 ? 'X' : 'O');
                break;
            }
            else if (choice == 2)
            {
                players[i] = createRandomPlayer(i == 0 ? 'X' : 'O');
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
    }
}

int main()
{
    int choice;
    cout << "Choose which game to play:" << endl;
    cout << "1 - Pyramidic Tic-Tac-Toe\n";
    cout << "2 - Word Tic-Tac-Toe\n";
    cout << "3 - Token Tick-Tac-Toe\n";
    cout << "4 - 5x5 Tic-Tac-Toe\n";
    cout << "5 - Misere Toe-Tac-Tic\n";
    cout << "6 - Four-In-Row\n";
    cout << "7 - Numerical Tic-Tac-Toe\n";
    cout << "8 - Ultimate Tic-Tac-Toe\n";
    cin >> choice;

    Player<char> *players[2] = {nullptr, nullptr};

    switch (choice)
    {
    case 1:
    { // Pyramidic Tic-Tac-Toe
        auto *board = new Pyramid_Board<char>();
        setupPlayers(
            players,
            [](const string &name, char symbol)
            { return new Pyramid_Player<char>(name, symbol); },
            [](char symbol)
            { return new Random_Pyramid_Player<char>(symbol); });
        GameManager<char> game(board, players);
        game.run();
        delete board;
        break;
    }
    case 2:
    { // Word Tic-Tac-Toe
        auto *board = new Word_Board<char>();
        setupPlayers(
            players,
            [](const string &name, char)
            { return new Word_Player<char>(name); },
            [](char)
            { return new Random_Word_Player<char>(); });
        GameManager<char> game(board, players);
        game.run();
        delete board;
        break;
    }
    case 3:
    { // Token Tic-Tac-Toe
        auto *board = new Token_X_O_Board<char>();
        setupPlayers(
            players,
            [](const string &name, char symbol)
            { return new Token_X_O_Player<char>(name, symbol); },
            [](char symbol)
            { return new Token_X_O_Random_Player<char>(symbol); });
        GameManager<char> game(board, players);
        game.run();
        delete board;
        break;
    }
    case 4:
    { // 5x5 Tic-Tac-Toe
        auto *board = new _5_X_O_Board<char>();
        setupPlayers(
            players,
            [](const string &name, char symbol)
            { return new _5x5_X_O_player<char>(name, symbol); },
            [](char symbol)
            { return new _5x5_X_O_Random_Player<char>(symbol); });
        GameManager<char> game(board, players);
        game.run();
        delete board;
        break;
    }
    case 5:
    { // Misere Tic-Tac-Toe
        auto *board = new Misere_X_O_Board<char>();
        setupPlayers(
            players,
            [](const string &name, char symbol)
            { return new Misere_X_O_Player<char>(name, symbol); },
            [](char symbol)
            { return new Misere_X_O_Random_Player<char>(symbol); });
        GameManager<char> game(board, players);
        game.run();
        delete board;
        break;
    }
    case 6:
    {
        int choice;
        Player<char> *players[2];
        FourInRowBoard<char> *B = new FourInRowBoard<char>();
        string player1Name, player2Name;

        cout << "Welcome to Four-in-a-Row!\n";

        // Set up player 1
        cout << "Enter Player 1 (X) name: ";
        cin >> player1Name;

        while (true)
        {
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number (1 or 2).\n";
                continue;
            }

            cin >> choice;
            if (choice == 1)
            {
                players[0] = new FourInRowPlayer<char>(player1Name, 'X');
                break;
            }
            else if (choice == 2)
            {
                players[0] = new Random_FourInRowPlayer<char>('X');
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
            break;
        }

        // Set up player 2
        cout << "Enter Player 2 (O) name: ";
        cin >> player2Name;

        while (true)
        {
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number (1 or 2).\n";
                continue;
            }

            cin >> choice;
            if (choice == 1)
            {
                players[1] = new FourInRowPlayer<char>(player2Name, 'O');
                break;
            }
            else if (choice == 2)
            {
                players[1] = new Random_FourInRowPlayer<char>('O');
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }

        // Assign the players to the board
        for (int i = 0; i < 2; ++i)
        {
            players[i]->setBoard(B);
        }

        // Create the game manager and run the game
        GameManager<char> FourInRow_game(B, players);
        FourInRow_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i)
        {
            delete players[i];
        }
        break;
    }
    case 7:
    { // Numerical Tic-Tac-Toe
        int option;
        Player<int> *players[2];
        NumBoard<int> *B = new NumBoard<int>();
        string player1Name, player2Name;

        cout << "Welcome to Numerical Tic Tac Toe!\n";

        // Set up player 1
        cout << "Enter Player 1 (Odd Numbers) name: ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";

        while (true)
        {
            cin >> option;
            if (option == 1 || option == 2)
            {
                break;
            }
            cout << "Invalid choice. Please choose again (1 or 2): ";
        }

        switch (option)
        {
        case 1:
            players[0] = new NumPlayer<int>(player1Name, {1, 3, 5, 7, 9});
            break;
        case 2:
            players[0] = new Random_NumPlayer<int>({1, 3, 5, 7, 9});
            break;
        default:
            cout << "Invalid choice. Exiting the game.\n";
            return 1;
        }

        // Set up player 2
        cout << "Enter Player 2 (Even Numbers) name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";

        while (true)
        {
            cin >> option;
            if (option == 1 || option == 2)
            {
                break;
            }
            cout << "Invalid choice. Please choose again (1 or 2): ";
        }

        switch (option)
        {
        case 1:
            players[1] = new NumPlayer<int>(player2Name, {2, 4, 6, 8});
            break;
        case 2:
            players[1] = new Random_NumPlayer<int>({2, 4, 6, 8});
            break;
        default:
            cout << "Invalid choice. Exiting the game.\n";
            return 1;
        }

        // Assign the players to the board
        for (int i = 0; i < 2; ++i)
        {
            players[i]->setBoard(B);
        }

        // Create the game manager and run the game
        GameManager<int> Num_game(B, players);
        Num_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i)
        {
            delete players[i];
        }
        break;
    }
    case 8:
    { // Ultimate Tic-Tac-Toe
        int option;
        Player<char> *players[2];
        Ultimate_Board<char> *B = new Ultimate_Board<char>();
        string playerXName, player2Name;

        cout << "Welcome to Ultimate Tic Tac Toe!\n";

        // Set up player 1
        cout << "Enter Player 1 name: ";
        cin >> playerXName;

        do
        {
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> option;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number (1 or 2).\n";
                continue;
            }

            if (option == 1)
            {
                players[0] = new Ultimate_Player<char>(playerXName, 'X');
                break;
            }
            else if (option == 2)
            {
                players[0] = new Ultimate_RandomPlayer<char>('X');
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        } while (true);

        // Set up player 2
        cout << "Enter Player 2 name: ";
        cin >> player2Name;

        do
        {
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> option;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a number (1 or 2).\n";
                continue;
            }

            if (option == 1)
            {
                players[1] = new Ultimate_Player<char>(player2Name, 'O');
                break;
            }
            else if (option == 2)
            {
                players[1] = new Ultimate_RandomPlayer<char>('O');
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        } while (true);

        // Create the game manager and run the game
        GameManager<char> ultimate_game(B, players);
        ultimate_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i)
        {
            delete players[i];
        }
        break;
    }
    default:
        if (choice > 6)
        {
            cout << "Invalid game choice. Exiting.\n";
        }

        return 1;
    }

    delete players[0];
    delete players[1];
    return 0;
}
