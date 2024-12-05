#ifndef Token_X_O
#define Token_X_O

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <iomanip>
using namespace std;

template <typename T>
class Token_X_O_Board : public Board<T>{
    public:
    Token_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Token_X_O_Player : public Player<T>{
    public:
    Token_X_O_Player(string n, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Token_X_O_Random_Player : public RandomPlayer<T>{
    public:
    Token_X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};




template <typename T>
Token_X_O_Board<T>::Token_X_O_Board(){
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++){
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++){
            if (i = 1 && j % 2 == 0){
                this->board[i][j] = 'O';
            }

            else if (i = 1 && j % 2 != 0){
                this->board[i][j] = 'X';
            }

            else if (i = 3 && j % 2 == 0){
                this->board[i][j] = 'X';
            }

            else if (i = 3 && j % 2 != 0){
                this->board[i][j] = 'O';
            }

            else{
                this->board[i][j] = 0;
            }                        
        }
    }

}

template <typename T>
bool Token_X_O_Board<T>::update_board(int x, int y, T symbol){
    string initial_coord = to_string(x);
    string dest_coord = to_string(y);
    int initial_x = initial_coord[0] - '0'; int initial_y = initial_coord[1] - '0';
    int dest_x = dest_coord[0] - '0'; int dest_y = dest_coord[1] - '0';

    //Checks if the initial and destination coordinates are valid in the board
    if ((initial_x >= 0 && initial_x < this->rows) && (initial_y >= 0 && initial_y < this->columns)
    && (dest_x >= 0 && dest_x < this->rows) && (dest_y >= 0 && dest_y < this->columns)){
        //Checks if the initial coordinates point to a player's token and the destination coordinates point to an empty cell
        if (this->board[initial_x][initial_y] = symbol && this->board[dest_x][dest_y] = 0){
            //Checks if the token will move vertically or horizontally only    
            if ((dest_x == initial_x && (dest_y == initial_y + 1 || dest_y == initial_y - 1))
            || (dest_y == initial_y && (dest_x == initial_x + 1 || dest_x == initial_x - 1))){

                this->board[initial_x][initial_y] = 0;
                this->board[dest_x][dest_y] = symbol;
                this->n_moves++;
                return true;
            }
        }
    }

    return false;
}

template <typename T>
void Token_X_O_Board<T>::display_board(){
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;    
}

template <typename T>
bool Token_X_O_Board<T>::is_win(){
    for (int i = 0; i < this->rows; i++){
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0)
        || (this->board[i][1] == this->board[i][2] && this->board[i][1] == this->board[i][3] && this->board[i][1] != 0)
        || (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)
        || (this->board[1][i] == this->board[2][i] && this->board[1][i] == this->board[3][i] && this->board[1][i] != 0)){
            return true;
        }
    }

    if ((this->board[0][0] == this->board[1][1] && this->board[0][0] == this->board[2][2] && this->board[0][0] != 0)
    || (this->board[1][1] == this->board[2][2] && this->board[1][1] == this->board[3][3] && this->board[1][1] != 0)
    || (this->board[3][0] == this->board[2][1] && this->board[3][0] == this->board[1][2] && this->board[3][0] != 0)
    || (this->board[2][1] == this->board[1][2] && this->board[2][1] == this->board[0][3] && this->board[2][1] != 0)
    || (this->board[2][0] == this->board[1][1] && this->board[2][0] == this->board[0][2] && this->board[2][0] != 0)
    || (this->board[3][1] == this->board[2][2] && this->board[3][1] == this->board[1][3] && this->board[3][1] != 0)
    || (this->board[0][1] == this->board[1][2] && this->board[0][1] == this->board[2][3] && this->board[0][1] != 0)
    || (this->board[1][0] == this->board[2][1] && this->board[1][0] == this->board[3][2] && this->board[1][0] != 0)){
        return true;
    }

    return false;
}

template <typename T>
bool Token_X_O_Board<T>::is_draw(){
    return false;
}

template <typename T>
bool Token_X_O_Board<T>::game_is_over(){
    return is_win();
}


template <typename T>
Token_X_O_Player<T>::Token_X_O_Player(string n, T symbol) : Player<T>(n, symbol){}

template <typename T>
void Token_X_O_Player<T>::getmove(int& x, int& y){
    cout << "\nEnter the initial and destination coordinates seperated by spaces (eg. 21 22 will move the token in cell (2,1) to (2,2)): ";
    cin >> x >> y;
}


template <typename T>
Token_X_O_Random_Player<T>::Token_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Token_X_O_Random_Player<T>::getmove(int& x, int& y){
    string initialx = to_string(rand() % this->dimension);
    string initialy = to_string(rand() % this->dimension);
    string destx = to_string(rand() % this->dimension);
    string desty = to_string(rand() % this->dimension);

    x = stoi(initialx + initialy);
    y = stoi(destx + desty);
}

#endif