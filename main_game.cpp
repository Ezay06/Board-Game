#include <iostream>
#include "BoardGame_Classes.h"
#include "PyramdicX_O.h"
#include "Word_TTO.h"
#include "Token_X_O.h"
using namespace std;

int main(){
    int choice;
    cout << "Choose which game to play:" << endl;
    cout << "1-Pyramidic Tic-Tac-Toe\n2-Word Tic-Tac-Toe\n3-Token Tick-Tack-Toe" << endl;
    cin >> choice;
    if (choice == 1){
        Player<char>* players[2];
        Pyramid_Board<char>* B = new Pyramid_Board<char>();
        string player1name, player2name;
        cout << "Enter Player X name: ";
        cin >> player1name;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[0] = new Pyramid_Player<char>(player1name, 'X');
                break;
            case 2:
                players[0] = new Random_Pyramid_Player<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }


        cout << "Enter Player 2 name: ";
        cin >> player2name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[1] = new Pyramid_Player<char>(player2name, 'O');
                break;
            case 2:
                players[1] = new Random_Pyramid_Player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

    
            GameManager<char> Pyramid_Game(B, players);
            Pyramid_Game.run();

            delete B;
            delete players[0];
            delete players[1];

            return 0;
    }


    else if (choice = 2){
        Player<char>* players[2];
        Word_Board<char>* B = new Word_Board<char>();
        string player1name, player2name;

        cout << "Enter Player X name: ";
        cin >> player1name;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[0] = new Word_Player<char>(player1name);
                break;
            case 2:
                players[0] = new Random_Word_Player<char>();
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }

        cout << "Enter Player 2 name: ";
        cin >> player2name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[1] = new Word_Player<char>(player2name);
                break;
            case 2:
                players[1] = new Random_Word_Player<char>();
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        GameManager<char> Word_Game(B, players);
        Word_Game.run();

        delete B;
        delete players[0];
        delete players[1];
    }

    else if (choice == 3){
        Player<char>* players[2];
        Token_X_O_Board<char>* B = new Token_X_O_Board<char>();
        string player1name, player2name;
        cout << "Enter Player X name: ";
        cin >> player1name;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[0] = new Token_X_O_Player<char>(player1name, 'X');
                break;
            case 2:
                players[0] = new Token_X_O_Random_Player<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }


        cout << "Enter Player 2 name: ";
        cin >> player2name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[1] = new Token_X_O_Player<char>(player2name, 'O');
                break;
            case 2:
                players[1] = new Token_X_O_Random_Player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

    
            GameManager<char> Pyramid_Game(B, players);
            Pyramid_Game.run();

            delete B;
            delete players[0];
            delete players[1];

            return 0;        
    }     
    
}